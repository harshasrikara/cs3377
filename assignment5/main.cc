
/*
 * Filename Main.cc
 * Date April 21st 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 * Description Starts a process that monitors a folder on the filesystem for changes. When detecting file modifications, it saves a copy  */

#include <iostream>
#include <fstream>
#include "enum.h"
#include "parseCommandLine.h"
#include "parseConfigFile.h"
#include "log.h"
#include "signalProcessing.h"
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

std::ofstream loggingFile;
std::map<keys, std::string> map;
std::ofstream pidFile;

int main(int argc, char *argv[]) {
  //parse the command line arguments
  int commandStatusCode = parseCommandLine(argc, argv, map);
  
  //exit if error occured in command line parsing
  if(commandStatusCode == 1) {
	return 1;
  }

  //parse the information in the configuration file
  int statusCode = parseConfigFile(map);

  //exit if there were any errors in parsing the configuration file
  if(statusCode == 1) {
	return 1;
  }

  //create log file
  loggingFile.open(map[logFile].c_str());

  if(!loggingFile) {
	std::cout << "Failed to create/open log file" << std::endl;
	return 1;
  }
  //only log if verbose mode is turned on
  if(map[verbose].length() == 4) {
	logConfigurationVariables(map, loggingFile);
  }

  pid_t forkvalue;
  //if running in daemon mode
  if(map[daemonX].length() == 4) {
	forkvalue = fork();	

	loggingFile << "Running in daemon mode" << std::endl;
  	if(forkvalue == -1) {
		loggingFile << "Error in creating fork" << std::endl;
		return 1;
  	}
  	else if(forkvalue == 0) {
		loggingFile << "daemon process pid: " << getpid() << std::endl;	
  	}
	else {
		if(map[verbose].length() == 4) {
			std::cout << "Parent exiting from daemon mode" << std::endl;
			loggingFile << "Parent exiting from daemon mode" << std::endl;
		}
		return 0;
	}
  }
  
  struct stat fileCheck;
  //check if the program is already running on the system
  std::string pidFileName =  "./cs3377dirmond.pid";
  if(stat(pidFileName.c_str(), &fileCheck) == 0) {
	std::cout << "daemon process already running, exiting program" << std::endl;
	loggingFile << "daemon process already running, exiting program" << std::endl;
	loggingFile.close();
	return 1;
  }

  //create pid file and save pid in it
  pidFile.open("cs3377dirmond.pid");
  if(!pidFile) {
	loggingFile << "Failed to create cs3377dirmond.pid file" << std::endl;
	return 1;
  }

  pidFile << getpid() << std::endl; 
  
  //setup signal processing
  signal(SIGINT, removeProcess);
  signal(SIGTERM, removeProcess);
  signal (SIGHUP, readConfigParameters);

  //chcek to see if the watch directory is present
  if(stat(map[watchDir].c_str(), &fileCheck) != 0) {
	loggingFile << "Watch Directory could not be found, exiting program" << std::endl;
	std::cout << "Watch Directory could not be found, exiting program" << std::endl;
	if(map[verbose].length() == 4) {
		loggingFile << "Please check the configuration variables set at: " << map[configFile] << std::endl;
		logConfigurationVariables(map, loggingFile);
	}
	return 1;
  }
  else {
  	std::cout << "Starting to track changes in: " << map[watchDir] << std::endl;
	loggingFile << "Starting to track changes in: " << map[watchDir] << std::endl;
  }

  //set up .versions folder or reuse if it already exists
  std::string versionFolder = map[watchDir] + "/.versions";
  if(stat(versionFolder.c_str(), &fileCheck) != 0) {
	loggingFile << ".versions subdirectory does not exist, creating new hidden folder" << std::endl;
	std::string command = "mkdir " + versionFolder;
	system(command.c_str());
  }


  while(true) {
  //set up inotify
  size_t bufferSize = sizeof(struct inotify_event) + PATH_MAX + 1;
  struct inotify_event *event = (struct inotify_event *) malloc(bufferSize);
  int length, watchDirectory;
  int fileDescriptor = inotify_init();
  int acc = 0;
  
  //test inotify
  if(fileDescriptor < 0) {
	loggingFile << "Inotify error in setup, exiting program" << std::endl;
	return 1;
  }

  watchDirectory = inotify_add_watch(fileDescriptor, map[watchDir].c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
  length = read(fileDescriptor, event, bufferSize);

  //check for errors in adding the watch and reading
  if(length < 0) {
	loggingFile << "Inotify error in setting watch, exiting program" << std::endl;
  }
  
  //monitor for changes
  if(acc < length) {

	if(event->len) {
		if(event->mask & IN_CREATE) {
			logFileCreate(event, loggingFile, map[verbose]);
		}
		if(event->mask & IN_MODIFY) {
			logFileModify(event, loggingFile, map[verbose]);

			//find the date
			char buffer[20];
			std::string command = "date +\"%Y.%m.%d-%T\"";
			FILE *date = popen(command.c_str(),"r");
			fread(buffer, sizeof(char), sizeof(char) * sizeof(buffer), date);
			int bufferlength = sizeof(buffer) / sizeof(buffer[0]);
			buffer[bufferlength-1] = '\0';

			//prepare command to copy the file over
			std::string copyFile = map[watchDir] + "/" + event->name;
			std::string pathInVersions = map[watchDir] + "/.versions/" + event->name + "." + buffer;
			command = "cp " + copyFile + " " + pathInVersions;

			//copy the file with timestamp over
			system(command.c_str());

			if(map[verbose].length() == 4) {
				loggingFile << "Finished copying modified file to .versions" << std::endl;
			}

		}
		if(event->mask & IN_DELETE) {
			logFileDeletion(event, loggingFile, map[verbose]);
		}
	}
	acc += sizeof(struct inotify_event) + event->len;
  }
  
  //clear memory and complete performing inotify actions
  inotify_rm_watch(fileDescriptor, watchDirectory);
  close(fileDescriptor);
  free(event);

  }

/*
  while(true) {
	loggingFile << "test" << std::endl;
  }*/

  remove("cs3377dirmond.pid");
  pidFile.close();
  loggingFile.close();

  std::cout << "successful exit" << std::endl;

  //exit successfully
  return 0;
}

void removeProcess(int signal) {
  remove("cs3377dirmond.pid");
  loggingFile << "SIGNINT/SIGTERM detected, gracefully shutting down" << std::endl;
  std::cout << "SIGINT/SIGTERM detected, gracefully shutting down" << std::endl;
  pidFile.close();
  loggingFile.close();
  exit(signal);
}

void readConfigParameters(int signal) {
  int statusCode = parseConfigFile(map);
  if(statusCode == 1) {
  	loggingFile << "Error occured in reading configuration file" << std::endl;
  	std::cout << "Error occured in reading configuration file" << std::endl;
 	remove("cs3377dirmond.pid");
	exit(signal);
  }
  loggingFile << "Configuration reset" << std::endl;
  logConfigurationVariables(map, loggingFile);
  loggingFile.close();
  loggingFile.open(map[logFile].c_str());
  logConfigurationVariables(map, loggingFile);
}



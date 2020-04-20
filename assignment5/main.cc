
#include <iostream>
#include <fstream>
#include "enum.h"
#include "parseCommandLine.h"
#include "parseConfigFile.h"
#include "log.h"
#include "signalProcessing.h"
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
  signal(SIGHUP, readConfigParameters);


  pidFile.close();
  loggingFile.close();

  std::cout << "successful exit" << std::endl;

  //exit successfully
  return 0;
}

void removeProcess(int signal) {
  remove("cs3377dirmond.pid");
  pidFile.close();
  loggingFile.close();
  exit(signal);
}

void readConfigParameters(int signal) {
  int statusCode = parseConfigFile(map);
  if(statusCode == 1) {
  	std::cout << "Error occured in reading configuration file" << std::endl;
 	exit(signal);
  }
  loggingFile << "Configuration reset" << std::endl;
  logConfigurationVariables(map, loggingFile);


}




/*
 * Filename log.cc
 * Date April 21st 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 * Description Contains the implementation for the log functions       */

#include "log.h"

//log all configuration variables
void logConfigurationVariables(std::map<keys, std::string> map, std::ofstream &loggingFile) {
  loggingFile << "daemon mode: " <<  map[daemonX] << std::endl;
  loggingFile << "configuration file: " <<  map[configFile] << std::endl;
  loggingFile << "verbose mode: " <<  map[verbose] << std::endl;
  loggingFile << "logging file: " << map[logFile] << std::endl;
  loggingFile << "password: " << map[password] << std::endl;
  loggingFile << "number of versions: " << map[numVersions] << std::endl;
  loggingFile << "watch directory: " << map[watchDir] << std::endl;
}

//log statement when a file gets created
void logFileCreate(struct inotify_event *e, std::ofstream &loggingFile, std::string verbose) {
  loggingFile << "Creation event occured" << std::endl;
  if(verbose.length() == 4) {
	if(e->mask & IN_ISDIR) {
		loggingFile << "Directory created with name: " << e->name << std::endl;
	}
	else {
		loggingFile << "File created with name: " << e->name << std::endl;
	}
  }
}

//log statement when file gets modified
void logFileModify(struct inotify_event *e, std::ofstream &loggingFile, std::string verbose) {
  loggingFile << "Modification event occured" << std::endl;
  if(verbose.length() == 4) {
	if(e->mask & IN_ISDIR) {
		loggingFile << "Directory modified with name: " << e->name << std::endl;
	}
	else {
		loggingFile << "File modified with name: " << e->name << std::endl;
	}
  }
}

//log statement when file gets deleted
void logFileDeletion(struct inotify_event *e, std::ofstream &loggingFile, std::string verbose) {
  loggingFile << "Deletion event occured" << std::endl;
  if(verbose.length() == 4) {
	if(e->mask & IN_ISDIR) {
		loggingFile << "Directory deleted with name: " << e->name << std::endl;
	}
	else {
		loggingFile << "File deleted with name: " << e->name << std::endl;
	}
  }
}





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




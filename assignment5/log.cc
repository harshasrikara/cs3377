
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





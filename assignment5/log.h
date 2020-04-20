

#ifndef LOG_H
#define LOG_H

#include "enum.h"

#include <map>
#include <string>
#include <fstream>
#include <signal.h>
#include <cstdlib>
#include <csignal>



void logConfigurationVariables(std::map<keys, std::string> map, std::ofstream &loggingFile);


#endif



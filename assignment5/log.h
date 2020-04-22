

#ifndef LOG_H
#define LOG_H

#include "enum.h"

#include <map>
#include <string>
#include <fstream>
#include <signal.h>
#include <cstdlib>
#include <csignal>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


void logConfigurationVariables(std::map<keys, std::string> map, std::ofstream &loggingFile);
void logFileCreate(struct inotify_event *e, std::ofstream &loggingFile, std::string verbose);
void logFileModify(struct inotify_event *e, std::ofstream &loggingFile, std::string verbose);
void logFileDeletion(struct inotify_event *e, std::ofstream &loggingFile, std::string verbose);

#endif



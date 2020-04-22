/*
 * Filename parseCommandLine.h
 * Date April 21st 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 *
 * Description header file for methods to read from command line, contains the tclap code */

#ifndef PARSE_COMMAND
#define PARSE_COMMAND

#include <iostream>
#include <map>
#include <exception>
#include <fstream>
#include <tclap/CmdLine.h>
#include <tclap/SwitchArg.h>
#include <tclap/ValueArg.h>
#include <tclap/UnlabeledValueArg.h>
#include "enum.h"

//function prototypes
int  parseCommandLine(int argc, char *argv[], std::map<keys, std::string> &map);
std::string convertBoolToString(bool a);

#endif

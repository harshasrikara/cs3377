/*
 * Filename parser.h
 * Date April 18th 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 *
 * Description <F6> */

#ifndef PARSE_CONFIG
#define PARSE_CONFIG

#include <iostream>
#include <map>
#include <exception>
#include <string.h>
#include <fstream>
#include <rude/config.h>
#include "enum.h"

int parseConfigFile(std::map<keys, std::string> &map);

#endif

/*
 * Filename parser.h
 * Date February 13th 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 *
 * Description converts text to uppercase/lowercase based on command line args */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <map>
#include <fstream>
#include <tclap/CmdLine.h>
#include <tclap/SwitchArg.h>
#include <tclap/ValueArg.h>
#include <tclap/UnlabeledValueArg.h>

enum keys
{
    upper,
    lower,
    outfile,
    infile
};

std::map<keys, std::string>  parseCommandLine(int argc, char *argv[]);
    std::string convertBoolToString(bool a);

#endif

/*
 * Filename parser.cc
 * Date February 13th 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 *
 * Description reads command line args */


#include "parser.h"

//will instatiate all tclap objects to make parse the command line and save them to a map
std::map<keys, std::string> parseCommandLine(int argc, char *argv[])
{
  std::map<keys, std::string> map;
    try {
        TCLAP::CmdLine cmd("Program will parse command line to receive arguments and use them to change text file to upper/lower case", ' ', "1.0");
        TCLAP::SwitchArg upperSwitch("u", "upper", "Convert all text to uppercase.", cmd, false);
        TCLAP::SwitchArg lowerSwitch("l", "lower", "Convert all text to lowercase.", cmd, false);
        TCLAP::ValueArg<std::string> outfileArg("o", "outfile", "The name of the output file", false, "output.txt", "output filename");
        TCLAP::UnlabeledValueArg<std::string> infileArg("infile", "The Input file name.", true, "infile.txt", "input filename", false);

        cmd.add(outfileArg);
        cmd.add(infileArg);

        cmd.parse(argc, argv);

        bool upperVal = upperSwitch.getValue();
        bool lowerVal = lowerSwitch.getValue();
        std::string outfileVal = outfileArg.getValue();
        std::string infileVal = infileArg.getValue();

        if(upperVal && lowerVal) {
            cmd.getOutput()->usage(cmd);
            throw new TCLAP::ArgException;
        }

        map.insert(std::make_pair(upper,convertBoolToString(upperVal)));
        map.insert(std::make_pair(lower,convertBoolToString(lowerVal)));
        map.insert(std::make_pair(outfile,outfileVal));
        map.insert(std::make_pair(infile,infileVal));

    }
    catch(TCLAP::ArgException exception) {
        std::cout << "Error Encountered: " << std::endl;
    }
    return map;
}

std::string convertBoolToString(bool a) {
    if(a) {
        return "true";
    }
    return "false";
}

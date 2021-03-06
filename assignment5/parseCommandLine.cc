/*
 * Filename parser.cc
 * Date April 21th 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 *
 * Description reads command line args */


#include "parseCommandLine.h"
#include "enum.h"

//will instatiate all tclap objects to make parse the command line and save them to a map
int parseCommandLine(int argc, char *argv[], std::map<keys, std::string> &map)
{
    try {
    	//instatiate variables
        TCLAP::CmdLine cmd("cs3377dirmond Directory Monitor Daemon", ' ', "1.0");
        TCLAP::SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as a daemon)", cmd, false);
        TCLAP::UnlabeledValueArg<std::string> confFileArg("configFile", "The name of the configuration file. Defaults to cs3377dirmond.conf", false, "cs3377dirmond.conf", "config filename", false);

        cmd.add(confFileArg);
	
	//parse the command line arguments
        cmd.parse(argc, argv);
	
	//convert to appropriate data types
        bool isDaemon = daemonSwitch.getValue();
        std::string confFile = confFileArg.getValue();
	
	//save in the map
        map.insert(std::make_pair(daemonX,convertBoolToString(isDaemon)));
        map.insert(std::make_pair(configFile,confFile));

    }
    catch(TCLAP::ArgException exception) {
        std::cout << "Error Encountered: TCLAP ArgException" << std::endl;
	return 1; //return error code
    }
    return 0; //return successfully
}

//converts to a string value so that it can be saved in the map
std::string convertBoolToString(bool a) {
    if(a) {
        return "true";
    }
    return "false";
}

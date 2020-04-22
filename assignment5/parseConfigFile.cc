/*
 * Filename parseCommandLine.cc
 * Date April 21st 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 * Description Utilize the rude library to parse the configuration file */

#include "parseConfigFile.h"

/**
 *
 * Return type is the status code, 0 for success, 1 for fail
 * Input parameter is the map of configuration values from both the command line and from the file, passed in by reference to get modified
 */
int  parseConfigFile(std::map<keys, std::string> &map) {
	rude::Config config;
	
	//Attempt to laod the configuration file and appropriately check for its status
	bool loadStatus = config.load(map[configFile].c_str());
	if(!loadStatus) {
		std::cout << "Configuration file not found" << std::endl;
		return 1;
	}

	//identify by looping through all the section if there exists one called Parameters
	bool doesSectionExist = false;
	std::string sectionName = "Parameters";
	for(int i = 0;i < config.getNumSections(); i++) {
		if(strcmp(config.getSectionNameAt(i), sectionName.c_str()) == 0) {
			doesSectionExist = true;
		}
	}
	if(!doesSectionExist) {
		std::cout << "Parameters section not found" << std::endl;
		return 1;
	}

	std::string emptyString = "";	
	//set section to parameters and retrieve values only after checking if they exist
	config.setSection("Parameters",false);
	
	//search for verbose parameter
	if(config.exists("Verbose")) {
		if(strcmp(map[verbose].c_str(), emptyString.c_str()) == 0) {
			map.erase(verbose);
	        	map.insert(std::make_pair(verbose, config.getStringValue("Verbose")));
		}
		else {  //overwrite parameter if changed at runtime
			map.erase(verbose);
			map.insert(std::make_pair(verbose, config.getStringValue("Verbose")));
		}
	}
	else {
		std::cout << "Verbose parameter not found" << std::endl;
		return 1;
	}
	
	//search for LogFile parameter
	if(config.exists("LogFile")) {
	        if(strcmp(map[logFile].c_str(), emptyString.c_str()) == 0) {
			map.erase(logFile);
       			map.insert(std::make_pair(logFile, config.getStringValue("LogFile")));
		}
		else {  //overwrite parameter if changed at runtime
			map.erase(logFile);
 			map.insert(std::make_pair(logFile, config.getStringValue("LogFile")));
		}
	}
	else {
		std::cout << "LogFile parameter not found" << std::endl;
		return 1;
	}
	
	//search for password parameter
	if(config.exists("Password")) {
		if(strcmp(map[password].c_str(), emptyString.c_str()) == 0) {
			map.erase(password);
	        	map.insert(std::make_pair(password, config.getStringValue("Password")));
		}
		else {  //ensure that it connot be overwritten at runtime
			if(strcmp(map[password].c_str(), config.getStringValue("Password")) != 0) {
				std::cout << "Error, attempting to modify password" << std::endl;
				return 1; //exit if password gets modified while daemon is running
			}
		}
	}
        else {
		std::cout << "Password parameter not found" << std::endl;
		return 1;
	}
	
	//search for numVersions parameter
	if(config.exists("NumVersions")) {
		if(strcmp(map[numVersions].c_str(), emptyString.c_str()) == 0) {
			map.erase(numVersions);
                	map.insert(std::make_pair(numVersions, config.getStringValue("NumVersions")));
		}
		else {  //overwrite if changed at runtime
			map.erase(numVersions);
			map.insert(std::make_pair(numVersions, config.getStringValue("NumVersions")));
		}
	}
	else {
 	        std::cout << "NumVersions parameter not found" << std::endl;
		return 1;
	}
	
	//search for watch directory parameter
	if(config.exists("WatchDir")) {
		if(strcmp(map[watchDir].c_str(), emptyString.c_str()) == 0) {
			map.erase(watchDir);
	        	map.insert(std::make_pair(watchDir, config.getStringValue("WatchDir")));
		}
		else {  //ensure that it cannot be overwritten at runtime
			if(strcmp(map[watchDir].c_str(), config.getStringValue("WatchDir")) != 0) {
				std::cout << "Error, attempting to modify watch directory" << std::endl;
				return 1; //exit if the watch directory gets modified while daemon is running
			}
		}
        }
	 else {
		std::cout << "WatchDir parameter not found" << std::endl;
		return 1;
	}
	return 0;

}

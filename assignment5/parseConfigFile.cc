
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

	if(config.exists("Verbose")) {
		if(strcmp(map[verbose].c_str(), emptyString.c_str()) == 0) {
			map.erase(verbose);
	        	map.insert(std::make_pair(verbose, config.getStringValue("Verbose")));
		}
		else {
			map.erase(verbose);
			map.insert(std::make_pair(verbose, config.getStringValue("Verbose")));
		}
	}
	else {
		std::cout << "Verbose parameter not found" << std::endl;
		return 1;
	}

	if(config.exists("LogFile")) {
	        if(strcmp(map[logFile].c_str(), emptyString.c_str()) == 0) {
			map.erase(logFile);
       			map.insert(std::make_pair(logFile, config.getStringValue("LogFile")));
		}
		else {
			map.erase(logFile);
 			map.insert(std::make_pair(logFile, config.getStringValue("LogFile")));
		}
	}
	else {
		std::cout << "LogFile parameter not found" << std::endl;
		return 1;
	}

	if(config.exists("Password")) {
		if(strcmp(map[password].c_str(), emptyString.c_str()) == 0) {
			map.erase(password);
	        	map.insert(std::make_pair(password, config.getStringValue("Password")));
		}
		else {
			if(strcmp(map[password].c_str(), config.getStringValue("Password")) != 0) {
				std::cout << "Error, attempting to modify password" << std::endl;
				return 1;
			}
		}
	}
        else {
		std::cout << "Password parameter not found" << std::endl;
		return 1;
	}

	if(config.exists("NumVersions")) {
		if(strcmp(map[numVersions].c_str(), emptyString.c_str()) == 0) {
			map.erase(numVersions);
                	map.insert(std::make_pair(numVersions, config.getStringValue("NumVersions")));
		}
		else {
			map.erase(numVersions);
			map.insert(std::make_pair(numVersions, config.getStringValue("NumVersions")));
		}
	}
	else {
 	        std::cout << "NumVersions parameter not found" << std::endl;
		return 1;
	}

	if(config.exists("WatchDir")) {
		if(strcmp(map[watchDir].c_str(), emptyString.c_str()) == 0) {
			map.erase(watchDir);
	        	map.insert(std::make_pair(watchDir, config.getStringValue("WatchDir")));
		}
		else {
			if(strcmp(map[watchDir].c_str(), config.getStringValue("WatchDir")) != 0) {
				std::cout << "Error, attempting to modify watch directory" << std::endl;
				return 1;
			}
		}
        }
	 else {
		std::cout << "WatchDir parameter not found" << std::endl;
		return 1;
	}
	return 0;

}

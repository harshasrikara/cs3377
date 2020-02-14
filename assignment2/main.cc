#include <iostream>
#include <algorithm>
#include <bits/stdc++.h> 
#include "parser.h"

std::string readFile(std::string infile);
void writeFile(std::string outfile, std::string text);
std::string uppercase(std::string text);
std::string lowercase(std::string text);

int main(int argc, char *argv[])
{
    parser commandLineParser;
    commandLineParser.parseCommandLine(argc, argv);
    std::map<key,std::string> map = commandLineParser.getMap();
    std::string data = readFile(map[infile]);
    writeFile(map[outfile], data);
    std::string rando = uppercase(data);
    return 0;
}

std::string readFile(std::string infile) {
    std::ifstream myInputFile;
    myInputFile.open(infile.c_str(), std::ios::in);
    std::string temp;
    std::string outputString;
    if(myInputFile) {
        while(getline(myInputFile,temp)) {
            outputString += temp + "\n";
        }
    }
    else {
        std::cout << "File IO error" << std::endl;
        exit(1);
    }
    myInputFile.close();
    return outputString;
}

std::string uppercase(std::string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}
std::string lowercase(std::string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

void writeFile(std::string outfile, std::string text) {
    std::ofstream myOutputFile;
    myOutputFile.open(outfile.c_str(), std::ios::out);
    myOutputFile << text << std::endl;
    myOutputFile.close();
}

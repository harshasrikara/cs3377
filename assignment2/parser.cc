#include "parser.h"

//constructor
parser::parser()
{

}

//will instatiate all tclap objects to make parse the command line and save them to a map
void parser::parseCommandLine(int argc, char *argv[])
{
    std::cout << "argument count: " << argc << std::endl;

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
}

std::string parser::convertBoolToString(bool a) {
    if(a) {
        return "true";
    }
    return "false";
}

//return map object
std::map<key, std::string> parser::getMap()
{
    return map;
}
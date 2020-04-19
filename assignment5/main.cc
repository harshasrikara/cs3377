#include <iostream>
#include "parser.h"

int main(int argc, char *argv[]) {
  std::map<keys, std::string> map = parseCommandLine(argc, argv);

  map = parseConfigFile(map);


  return 0;
}

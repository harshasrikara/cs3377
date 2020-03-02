/*
 * Filename Main.cc
 * Date March 1st 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 *
 * Description executes a gawk command and retrieves the output of that command to be added up*/


#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "adder.h"

#define BUFFER_SIZE 1024


int main(int argc, char *argv[])
{
  FILE *output_from_command;
  char tmpbuffer[BUFFER_SIZE];
  char *line_p;

  std::string shellcmd = "./bin/gawk --version";

  std::cout << std::endl;
  std::cout << "The first call to gawk returned:: " << std::endl;
  std::cout << std::endl;
  
  output_from_command = popen(shellcmd.c_str(), "r");

  if (!output_from_command) {
    return -1;
  }

  line_p = fgets(tmpbuffer, BUFFER_SIZE, output_from_command);
  while(line_p != NULL)
    {
      printf("\t%s", line_p);
      line_p = fgets(tmpbuffer, BUFFER_SIZE, output_from_command);
    }
  pclose(output_from_command);
  std::cout << std::endl;
  std::cout << std::endl;


  shellcmd = "./bin/gawk -f gawk.code numbers.txt";

  std::cout << std::endl;
  std::cout << "The second call to gawk returned:: ";

  output_from_command = popen(shellcmd.c_str(), "r");

  if (!output_from_command) {
    return -1;
  }

  line_p = fgets(tmpbuffer, BUFFER_SIZE, output_from_command);
  printf("%s", line_p);
  int total = sum(line_p);
  std::cout << "The sum of the two numbers is " << total << std::endl;
  std::cout << std::endl;
  return 0;
}

/*
 * Filename adder.cc
 * Date March 1st 2020
 * Author Harsha Srikara
 * Email hxc170009@utdallas.edu
 * Course CS3377.501
 * Version 1
 * Copyright Harsha Srikara
 *
 * Description adds two numbers */

#include "adder.h"

int sum(char *line) {
  std::istringstream istream(line);
  int column1;
  int column4;
  istream >> column1 >> column4;
  std::cout << "The sum of column 1 is " << column1 << std::endl;
  std::cout << "The sum of column 2 is " << column4 << std::endl;
  int total = column1 + column4;
  return total;
}

//Name: Harsha Srikara
//Course: CS 3377
//Assignment: Assignment 1
//Email: hxc170009@utdallas.edu
//Date: Jan 30
//Version: 1
//Copyright: 2020, All Rights reserved

//Description: C++ file that prints arguments and count and also calls another function in a diff file

#include<iostream>
#include "function.h"

int main(int argc, char *argv[]) {
     std::cout << "therer are " << argc << " arguments" << std::endl;

     for(int i = 0; i < argc; i++ ) {
          std::cout << argv[i] << std::endl;
     }

     std::cout << "inside main.cpp" <<std::endl;

     function();

     return 0;

 }

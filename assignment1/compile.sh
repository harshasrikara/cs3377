#!/bin/bash


#Name: Harsha Srikara
#Course: CS 3377
#Assignment: Assignment one
#Date: Jan 30 2020
#Email: hxc170009@utdallas.edu
#Version: 1
#Description: Compiles to object files and then links them together

echo "starting to compile"
g++ -c ./main.cpp ./function.cpp
echo "starting to link"
g++ main.o function.o
echo "complete"

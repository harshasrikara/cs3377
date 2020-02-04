#!/bin/bash

#Name: Harsha Srikara
#Course: CS3377
#Email: hxc170009@utdallas.edu
#Date: Jan 30 2020
#Assignment: 1
#version: 1
#Description: compiles the file and runs with a set of test arguments

echo "compiling and linking"
./compile.sh

echo "running with no parameters"
./a.out >> stdout.log 2>> stderr.log

echo "running with one parameter"
./a.out bob >> stdout.log 2>> stderr.log

echo "running with two parameters"
./a.out bob truck >> stdout.log 2>> stderr.log

echo "running with three parameters"
./a.out bob truck train >> stdout.log 2>> stderr.log

echo "complete"

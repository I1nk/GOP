#!/bin/bash

clear
rm gop.out
gcc -Wall -c gop.c -O2
gcc -static gop.o -lm -o gop.out 


#!/bin/bash

clear
rm gop.out

#below is to complie the code to run with valgrind
gcc -Wall -g gop.c -o gop.out

#normal complie 
#gcc -Wall -O2 gop.c -o gop.out

#For math.h
#gcc -Wall -c -O2 gop.c

#below are the lines to link the code to math.h
##-O2
##gcc -static gop.o -lm -o gop.out 
##rm gop.o


##valgrind -v --leak-check=yes ./file

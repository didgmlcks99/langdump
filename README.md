# langdump - buildscript

## Inputs

### This program receives a txt file in which holds a recursively defined rule of a grammar and an integer value in which limits the member string to be printed to the standard output.

<br>

## Program Description

### This program prints all the member strings of a set of strings according to the given recursively defined grammar rule, satisfying a length less than the given constraint.

<br>

## Comiling and Run
* 1. 'make' : run the command, 'make' on the terminal to compile and make a executable file of 'langdump.
* 2. './langdump \<grammar-description-file> \<max-length>': run the executable file created from step 1 with the command './langdump' including the correct arguments for the program.

<br>

## Input Guide
* \<grammar-description-file> input must be a .txt file in which defines the rule of grammar of certain set of string recursively.

* \<max-length> input must be a integer between 1 and 64. This integer is the limit in which the length of the printed member strings must satisfy.

<br>

## Makefile
* This file automatically runs the command for compiling the 'langdump.c' file.

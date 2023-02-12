# 16-Bit Assembly Compiler

The Author: Omer Levy
Course instructor: Nadav Beno
Date of Submission: 14 August, 2022

Introduction :
	This project is an assignment in a C programming course No. 20465 at the open University (aka openU).
	The purpose of this project is to build an assembler for 16 instruction assembly language,
	for an imaginary 24-bit CPU and 21 bits of memory size.

File Summary :
	main - The main function used as a base frame of the program.
	globalFun - Conation of all the includes and typedef enums to be used by all code files
	LineManager - Oversees the functions of files and linked nodes.
	macroManager - Create a code layout without Macros for later stages of the program.
	firstRun - Goes through by each line and map it by symbols, types and dates for the second run.
	secondRun - Reserved a mapped source code and create the machine code by compile it.
	fileOutput - this function is responsible for extracting the information onto the needed files.
	makefile - the makefile needed to run the program on a GCC compiler

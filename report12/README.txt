//Program Submitted for プログラミング通論 on 08/08/2021 by Saurabh Sharma

Program Description
	Converts RGB Images to Grayscale in Parallel by Multi-Threading

Program Requirement (Files)
	1. main.c
	2. JpegReadWrite.c
	3. some images (.jpg formatted)
	4. Makefile

How to compile:
	On terminal, type "make all". On successfull compilation, main.o and JpegReadWrite.o will be generated. Note that, "make" needs to be installed on your system.

How to run (conversion):
	After successful compilation, type ./main filename1.jpg filename2.jpg ...


Program Documentation:

Line 8
	- Declaration of global variable argp

Lines 10
	- Declaration of routine function (this converts a single rgb image to jpg)

Lines 12 - 48
	- main function

	Line 15
		- assigning argv to global variable argp

	Line 16
		- initializing thread of size argc - 1 (as the first argument is program name)

	Line 18-19 & 29-42
		- time calculation and printing

	Line 21-27
		- creating required number of threads using pthread_create and pthread_join in for loop each, sending each command line argument per thread

Lines 48 - 95
	- routine function definition

	Line 50-61
		- Declaration of variables

	Line 63 
		- copying filename to IntputFileName

	Line 64
		- checking for .jpg extension in IntputFileName

	Line 65-68
		- printing error, if extension mismatch

	Line 69-76
		- performing rename operation with _gray, and writing to OutputFileName

	Line 78-81
		- error printing, if decode error

	Line 85-91
		- converting rgb image to grayscale image, and writing to the OutputFileName created on lines 69-76

	Line 93
		- releasing raw memory

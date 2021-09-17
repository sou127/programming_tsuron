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


Lines 8-51: routine function (converts a single rgb image to gray) 
	Line 9-18
		- Declaration of variables
	Line 20 
		- copying filename to IntputFileName
	Line 21-25
		- error handling for extension mismatch
	Line 26-33
		- performing rename operation with _gray, and writing to OutputFileName
	Line 35-38
		- error handling for decode error
	Line 42-48
		- converting rgb image to grayscale image, and writing to the OutputFileName
	Line 50
		- releasing raw memory


Lines 53-85: main function
	Line 55
		- declaring required number of threads
	Line 18-19 & 29-42
		- time calculation (before & after finishing the conversion operation)
	Line 21-27
		- calling conversion function (routine) through the threads

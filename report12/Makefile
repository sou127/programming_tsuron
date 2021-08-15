.PHONY: all
obj = main.o JpegReadWrite.o
LIB = -ljpeg -pthread

all: main

main: main.o JpegReadWrite.o
	gcc -o main $(obj) $(LIB)

main.o: main.c
	gcc -c main.c

JpegReadWrite.o: JpegReadWrite.c
	gcc -c JpegReadWrite.c

sample: sample.o JpegReadWrite.o
	gcc -o sample sample.c JpegReadWrite.o $(LIB)

sample.o: sample.c
	gcc -c sample.c

.PHONY: clean
clean:
	rm -f main $(obj)
allclean:
	rm -f main sample sample.o $(obj) *~ *gray*

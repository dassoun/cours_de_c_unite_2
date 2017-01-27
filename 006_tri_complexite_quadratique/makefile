test.exe : test.o intarray.o tools.o jstr.o stringarray.o
	gcc test.o intarray.o tools.o jstr.o stringarray.o -o test.exe

intarray.o : intarray.c intarray.h tools.h
	gcc -c intarray.c

jstr.o : jstr.c jstr.h tools.h intarray.o
	gcc -c jstr.c

stringarray.o : stringarray.c stringarray.h jstr.h tools.h
	gcc -c stringarray.c

test.o : test.c intarray.h tools.h jstr.h stringarray.h
	gcc -c test.c

tools.o : tools.c tools.h
	gcc -c tools.c

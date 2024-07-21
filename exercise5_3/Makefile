all:
	gcc -fPIC -c add.c subtract.c multiply.c divide.c max.c min.c -std=c99
	gcc -shared add.o -o libadd.so
	gcc -shared subtract.o -o libsubtract.so
	gcc -shared multiply.o -o libmultiply.so
	gcc -shared divide.o -o libdivide.so
	gcc -shared max.o -o libmax.so
	gcc -shared min.o -o libmin.so
	gcc main.c -o main -ldl -std=c99
clean:
	rm -f *.o *.so main

a2q1: q1_function.o q1.o
	gcc -Wall -std=c99 -pendantic q1_function.o q1.o -o a2q1

q1_function.o: q1_function.c q1_function.h
	gcc -Wall -std=c99 -pendantic -c q1_function.c -o q1_function.o

q1.o: q1.c q1_function.h
	gcc -Wall -std=c99 -pendantic -c q1.c -o q1.o

clean:
	rm -f *.o a2q1
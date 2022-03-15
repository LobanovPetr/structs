CC=gcc

CFLAGS= -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wno-format \
-Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors \


run: main.o array.o
	gcc -o run main.o array.o

main.o: main.c
	gcc -c -o main.o main.c

array.o: array.c
	gcc -c -o array.o array.c

clean:
	rm -rf *.o


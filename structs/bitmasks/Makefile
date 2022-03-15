all : run

run : main.o bitmasks.o
	g++ -std=c++11 main.o bitmasks.o -o run

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

bitmasks.o : bitmasks.cpp
	g++ -std=c++11 -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=2 -Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors -Wunused -Wuninitialized -fPIC -c bitmasks.cpp

clean:
	rm -rf *.o
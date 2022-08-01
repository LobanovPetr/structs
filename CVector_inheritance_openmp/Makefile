CPP_FLAGS= -std=c++11 -fopenmp -O3 -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute  -Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wunused -Wuninitialized -fPIC

headers = -I/usr/local/include
lib = -L/usr/local/lib
cc = clang++

all: run
run: main.o CVector1.o CVector0.o CVector.o
	$(cc) ${CPP_FLAGS} $(lib) -o run main.o CVector0.o CVector1.o CVector.o -lomp
main.o: main.cpp
	$(cc) ${CPP_FLAGS} $(headers) -c main.cpp
CVector1.o: CVector1.cpp
	$(cc) ${CPP_FLAGS} -c CVector1.cpp
CVector0.o: CVector0.cpp
	$(cc) ${CPP_FLAGS} -c CVector0.cpp
CVector.o: CVector.cpp
	$(cc) ${CPP_FLAGS} -c CVector.cpp
clean:
	rm *.o run*

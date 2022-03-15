CPP_FLAGS= -std=c++11 -Xpreprocessor -fopenmp

path = -I/usr/local/include -L/usr/local/lib

all: run
run: main.o CVector1.o CVector0.o CVector.o
	g++ ${CPP_FLAGS} $(path) -lomp main.o CVector0.o CVector1.o CVector.o -o run
main.o: main.cpp
	g++ ${CPP_FLAGS} -c main.cpp
CVector1.o: CVector1.cpp
	g++ ${CPP_FLAGS} -c CVector1.cpp
CVector0.o: CVector0.cpp
	g++ ${CPP_FLAGS} -c CVector0.cpp
CVector.o: CVector.cpp
	g++ ${CPP_FLAGS} -c CVector.cpp
clean:
	rm *.o run*

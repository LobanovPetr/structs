all : run

run: main.o CVector.o
	g++ -std=gnu++11 main.o CVector.o -o run

main.o: main.cpp
	g++ -std=gnu++11 -c main.cpp

CVector.o: CVector.cpp
	g++ -std=gnu++11 -c CVector.cpp



clean:
	rm -rf *.o

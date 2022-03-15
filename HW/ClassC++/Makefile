all : run

main.o: main.cpp
	g++ -c main.cpp

CRat.o: CRat.cpp
	g++ -c CRat.cpp

run: main.o CRat.o
	g++ main.o CRat.o -o run

clean:
	rm -rf *.o


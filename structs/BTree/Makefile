all : run

run: main.o B_tree.o
	g++ main.o B_tree.o -o run

main.o: main.cpp
	g++ -c main.cpp

CVector.o: B_tree.cpp
	g++ -c B_tree.cpp

clean:
	rm -rf *.o
all: p7

p7: project7.o PolyNom.o
	g++ project7.o PolyNom.o -o p7

project7.o: project7.cpp
	g++ -c project7.cpp

PolyNom.o: PolyNom.cpp
	g++ -c PolyNom.cpp

clean:
	rm -f *.o p7

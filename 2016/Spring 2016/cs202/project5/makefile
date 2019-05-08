all: p5

p5: project5.o String.o
	g++ project5.o String.o -o p5

project5.o: project5.cpp
	g++ -c project5.cpp

String.o: String.cpp
	g++ -c String.cpp

clean:
	rm -f *.o p5

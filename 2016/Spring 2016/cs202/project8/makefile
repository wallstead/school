all: p8

p8: project8.o stack3.o
	g++ project8.o stack3.o -o p8

project8.o: project8.cpp
	g++ -c project8.cpp

stack2.o: stack2.cpp
	g++ -c stack2.cpp

stack3.o: stack3.cpp
	g++ -c stack3.cpp

clean:
	rm -f *.o p8

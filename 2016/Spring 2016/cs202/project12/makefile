all: p12

p12: main.o inheritance.o
	g++ main.o inheritance.o -o p12

main.o: main.cpp
	g++ -c main.cpp

inheritance.o: inheritance.cpp
	g++ -c inheritance.cpp

clean:
	rm -f *.o p12

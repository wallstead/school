all: p9

p9: main.o queue3.o
	g++ main.o queue3.o -o p9

main.o: main.cpp
	g++ -c main.cpp

queue3.o: queue3.cpp
	g++ -c queue3.cpp

clean:
	rm -f *.o p9

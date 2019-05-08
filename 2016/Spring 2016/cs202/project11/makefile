all: p11

p11: main.o listarray.o listnode.o
	g++ main.o listarray.o listnode.o -o p11

main.o: main.cpp
	g++ -c main.cpp

listarray.o: listarray.cpp
	g++ -c listarray.cpp

listnode.o: listnode.cpp
	g++ -c listnode.cpp

clean:
	rm -f *.o p11

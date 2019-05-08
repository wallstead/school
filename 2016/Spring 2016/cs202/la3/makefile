all: la3

la3: main.o stack.o
	g++ main.o stack.o -o la3

main.o: main.cpp
	g++ -c main.cpp

stack.o: stack.cpp
	g++ -c stack.cpp

clean:
	rm -f *.o la3

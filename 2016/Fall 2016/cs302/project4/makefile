all: PA04

PA04: PA04.o Bubble.o Merge.o Counting.o
	g++ PA04.o Bubble.o Merge.o Counting.o -o PA04

PA04.o: PA04.cpp
	g++ -c PA04.cpp

Bubble.o: Bubble.cpp
	g++ -c Bubble.cpp

Merge.o: Merge.cpp
	g++ -c Merge.cpp

Counting.o: Counting.cpp
	g++ -c Counting.cpp

clean:
	rm -f *.o PA04

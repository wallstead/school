all: p6

p6: project5.o Agency.o
	g++ project6.o Agency.o -o p6

project5.o: project6.cpp
	g++ -c project6.cpp

Agency.o: Agency.cpp
	g++ -c Agency.cpp

clean:
	rm -f *.o p6

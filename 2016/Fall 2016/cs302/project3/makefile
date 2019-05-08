all: PA03

PA03: PA03.o City.o Stack.o FlightMap.v1.o
	g++ PA03.o City.o Stack.o FlightMap.v1.o -o PA03

PA03.o: PA03.cpp
	g++ -c PA03.cpp

City.o: City.cpp
	g++ -c City.cpp

Stack.o: Stack.cpp
	g++ -c Stack.cpp

FlightMap.v1.o: FlightMap.v1.cpp
	g++ -c FlightMap.v1.cpp

clean:
	rm -f *.o PA03

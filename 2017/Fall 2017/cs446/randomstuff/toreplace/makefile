Sim02: Sim02.cpp Simulator.o Logger.o Timer.o
	g++ -std=c++11 -pthread Sim02.cpp Simulator.o Logger.o Timer.o -o Sim02

Simulator.o: Simulator.cpp
	g++ -c Simulator.cpp -std=c++11 -pthread

Logger.o: Logger.cpp
	g++ -c Logger.cpp -std=c++11

Timer.o:: Timer.cpp
	g++ -c Timer.cpp -std=c++11

clean:
	rm *.o Sim02

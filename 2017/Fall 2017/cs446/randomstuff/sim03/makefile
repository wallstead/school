CFLAGS = -std=c++11

Sim03: Sim03.cpp Simulator.o OutputLog.o Timer.o
	g++ -std=c++11 -pthread Sim03.cpp Simulator.o OutputLog.o Timer.o -o sim03

Simulator.o: Simulator.cpp 
	g++ -c Simulator.cpp -std=c++11 -pthread

OutputLog.o: OutputLog.cpp
	g++ -c OutputLog.cpp -std=c++11

Timer.o:: Timer.cpp
	g++ -c Timer.cpp -std=c++11

clean:
	rm *.o sim03

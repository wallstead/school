CFLAGS = -std=c++11

Sim05: Sim05.cpp Simulator.o OutputLog.o Timer.o
	g++ -std=c++11 -pthread Sim05.cpp Simulator.o OutputLog.o Timer.o -o sim05

Simulator.o: Simulator.cpp 
	g++ -c Simulator.cpp -std=c++11 -pthread

OutputLog.o: OutputLog.cpp
	g++ -c OutputLog.cpp -std=c++11

Timer.o:: Timer.cpp
	g++ -c Timer.cpp -std=c++11

clean:
	rm *.o sim05

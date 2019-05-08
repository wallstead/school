CFLAGS = -std=c++11

Sim02: Sim02.cpp Simulator.o OutputLog.o Process.o Timer.o
	g++ -std=c++11 -pthread Sim02.cpp Simulator.o OutputLog.o Process.o Timer.o -o sim02

Simulator.o: Simulator.cpp 
	g++ -c Simulator.cpp -std=c++11 -pthread

OutputLog.o: OutputLog.cpp
	g++ -c OutputLog.cpp -std=c++11

Process.o: Process.cpp
	g++ -c Process.cpp -std=c++11 -pthread

Timer.o:: Timer.cpp
	g++ -c Timer.cpp -std=c++11

clean:
	rm *.o sim02

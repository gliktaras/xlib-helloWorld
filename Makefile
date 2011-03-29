build: Game.h Game.cpp HelloWorld.cpp HelloWorld.h main.cpp
	g++ -O2 -lX11 -Wall -o helloWorld Game.cpp HelloWorld.cpp main.cpp

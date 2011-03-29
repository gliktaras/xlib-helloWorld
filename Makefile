build: HelloWorld.cpp HelloWorld.h main.cpp
	g++ -O2 -lX11 -Wall -o helloWorld HelloWorld.cpp main.cpp

FILES = Neuron.cpp Net.cpp main.cpp

all: 
	g++ $(FILES) -lstdc++ -std=c++11 -Wall -I. -o main

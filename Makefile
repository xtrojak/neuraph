FILES = Neuron.cpp

all: 
	gcc $(FILES) -std=c++11 -I. -o main

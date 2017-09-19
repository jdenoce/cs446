
main: config_data.o meta_data.o node.o
		g++ -c main.cpp
		g++ main.o config_data.o meta_data.o node.o -o sim01

config_data.o: config_data.cpp config_data.h meta_data.h node.h
		g++ -c config_data.h
		g++ -c config_data.cpp

meta_data.o: meta_data.cpp meta_data.h node.h
		g++ -c meta_data.h
		g++ -c meta_data.cpp

node.o: node.cpp node.h
		g++ -c node.h
		g++ -c node.cpp

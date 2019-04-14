# makefile

all: shell

shell.o: shell.cpp
	g++ -g -w -std=c++14 -c shell.cpp

shell: shell.cpp commands.h utils.h
	g++ -g -w -std=c++14 -o shell shell.cpp commands.h utils.h -lpthread -lrt

clean:
	rm -rf *.o *.csv shell

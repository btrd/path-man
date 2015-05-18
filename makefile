CC=gcc
CXX=g++
CFLAGS=-Wall -g -lrpcsvc -std=c99
CXXFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -Wall -g
SOURCES=Map.cpp Point.cpp Person.cpp Village.cpp Genome.cpp Client.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=Server Client

all : $(EXEC)

Server : Server.o xdr_population.o
	$(CC) -o $@ Server.o xdr_population.o

Client : $(OBJECTS) callRpc.o
	$(CXX) -o $@ $(OBJECTS) xdr_population.o callRpc.o $(CXXFLAGS)

xdr_population.o: xdr_population.c include.h
	$(CC) -o $@ -c xdr_population.c -W -Wall -ansi -pedantic

callRpc.o: callRpc.c include.h
	$(CC) -o $@ -c callRpc.c -W -Wall -ansi -pedantic

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	rm -f ${EXECUTABLE} *.o
	rm -fr Server.dSYM
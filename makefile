CC=gcc
CXX=g++
CFLAGS=-Wall -g -std=c99
CXXFLAGS=-Wall -g
SOURCES=Map.cpp Point.cpp Person.cpp Village.cpp Genome.cpp Client.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=Server Client

all : $(EXEC)

Server : Server.o xdr_population.o
	$(CC) -o $@ Server.o xdr_population.o

Client : $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

%.o: %.c
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	rm -f a.out ${EXECUTABLE}
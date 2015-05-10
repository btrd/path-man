CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Map.cpp Point.cpp Person.cpp Village.cpp Genome.cpp Client.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f a.out ${EXECUTABLE}
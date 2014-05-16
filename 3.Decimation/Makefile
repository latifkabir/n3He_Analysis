#Latiful Kabir
#Makefile for Decimation and averaging
#Date:05.09.14



CXX=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=average
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	       $(CXX) $(LDFLAGS) $(OBJECTS) -o $@
%.o:%.cpp
	$(CXX) $(CFLAGS) $< -o $@

clear:
	rm -f src/*.o

clean:
	rm -f src/*.o $(EXECUTABLE)






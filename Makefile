# Makefile for FinalProject
# Use 'make all' in the terminal to compile all dependencies and the
# driver program for the sort functions. When the program is ran it 
# will produce output in Data/ which will get deleted on 'make clean'

TARGET = FinalProject
LIBS =  #None
HEADERS = neighbor.h city_node.h Cities.h
SRCS = FinalProject.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SRCS))
CXX = g++
CXX_FLAGS = -Wall 

.PHONY: default all clean

all: depend $(TARGET)

#Rules to recompile template headers when they change
depend: .depend
.depend: $(HEADERS)
	rm -f ./.depend
	$(CXX) $(CXX_FLAGS) -MM $^ > ./.depend;
include .depend

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f ./.depend
	-rm -f $(TARGET)
	-rm -f output.txt


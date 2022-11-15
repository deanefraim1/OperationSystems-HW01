# Makefile for the smash program
CXX = g++
CXXFLAGS = -g -Wall -std=c++20
CXXLINK = $(CXX)
OBJS = smash.o commands.o signals.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
commands.o: commands.cpp commands.hpp
smash.o: smash.cpp commands.hpp
signals.o: signals.cpp signals.hpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*


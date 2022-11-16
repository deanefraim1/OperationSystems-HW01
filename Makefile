# Makefile for the smash program
CXX = g++
CXXFLAGS = -g -Wall -std=c++17
CXXLINK = $(CXX)
OBJS = smash.o commands.o signals.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CXXLINK) -o smash $(OBJS)
# Creating the object files
smash.o: smash.cpp commands.hpp commands.hpp signals.hpp Job.hpp
commands.o: commands.cpp commands.hpp Job.hpp
signals.o: signals.cpp signals.hpp
Job.o: Job.cpp Job.hpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*


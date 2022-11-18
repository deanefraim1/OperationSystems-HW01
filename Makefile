# Makefile for the smash program
CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CXXLINK = $(CXX)
OBJS = smash.o commands.o signals.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CXXLINK) -o smash $(OBJS)
# Creating the object files
smash.o: smash.cpp commands.hpp signals.hpp Job.hpp Shell.hpp
commands.o: commands.cpp commands.hpp Job.hpp Shell.hpp
signals.o: signals.cpp signals.hpp Shell.hpp
Job.o: Job.cpp Job.hpp
Shell.o: Shell.cpp Shell.hpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*


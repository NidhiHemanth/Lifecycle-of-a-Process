# Type of compiler
CC = g++
# C++ standards used
LFLAGS = -std=c++11
# Compiler option. -c is for compilation. -Wall is for warning
CFLAGS = -c -Wall

# EXECUTABLE_NAME is the name of the program to run
# SOURCES include all the .cpp files to compile
EXECUTABLE_NAME = os
SOURCES = main.cpp Memory.cpp CPU.cpp IO.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)

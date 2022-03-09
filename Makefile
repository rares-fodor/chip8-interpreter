# Which compiler will be used.
CC=gcc

# CFLAGS specifies compiler options
CFLAGS=-c -std=c99 -Wall -Wextra -O2

# Compiler and linker options for SDL2
SDL_CFLAGS= $(shell sdl2-config --cflags)
SDL_LFLAGS= $(shell sdl2-config --libs)

override CFLAGS += $(SDL_CFLAGS)

# Directory paths for the Header files and the Source files
SOURCEDIR= src/

SOURCE_FILES= main.c chip8.c instructions.c

SOURCE_FP = $(addprefix $(SOURCEDIR),$(SOURCE_FILES))

# Create the object files
OBJECTS =$(SOURCE_FP:.c = .o)

# Program to build
EXECUTABLE=chip8

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(SDL_LFLAGS) -o $(EXECUTABLE)

%.o: %.c 
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -rf src/*.o $(EXECUTABLE)



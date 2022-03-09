CC=gcc
CFLAGS=-c -Wall -g


EXEC=chip8

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LFLAGS) -o $(EXEC)

%.o: %.c 
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -rf src/*.o $(EXEC)



CC = gcc
CFLAGS = #-Wall -Wextra -Werror -O3
INCLUDES = -I./src

SRC = src/main.c src/solver.c src/utils.c
OBJ = $(SRC) #:.c=.o

# Output executable name
EXEC = main

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS) $(LDFLAGS)

# Clean rule to remove object files and the executable
clean:
	rm -f src/*.o $(EXEC)

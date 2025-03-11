CC = gcc
CFLAGS = #-Wall -Wextra -Werror -O3
INCLUDES = -I./src

SRC = src/main.c src/solver.c src/sudoku_utils.c src/helper_funcs.c
OBJ = $(SRC) #:.c=.o

# Output executable name

main: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS) $(LDFLAGS)

test: src/test_shii.c src/sudoku_utils.c src/helper_funcs.c
	$(CC) -o test src/test_shii.c src/sudoku_utils.c src/helper_funcs.c $(CFLAGS) $(INCLUDES)


# Clean rule to remove object files and the executable
clean:
	rm -f src/*.o main test

CC = gcc
CFLAGS = -Ofast -march=native -funroll-loops -ftree-vectorize -fopt-info-vec-optimized -O3 -Wall -Wextra -Werror #-fopenmp 
INCLUDES = -I./src

SRC = src/main.c src/solver.c src/sudoku_utils.c src/helper_funcs.c
OBJ = $(SRC) #:.c=.o


# valgrind --tool=cachegrind --branch-sim=yes # for cache profiling - branch mispredicts
# valgrind --tool=cachegrind --cache-sim=yes

main: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS) $(LDFLAGS)

debug: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS) $(LDFLAGS) -g

test: src/test_shii.c src/sudoku_utils.c src/helper_funcs.c
	$(CC) -o test src/test_shii.c src/sudoku_utils.c src/helper_funcs.c $(CFLAGS) $(INCLUDES)


# Clean rule to remove object files and the executable
clean:
	rm -f src/*.o main test

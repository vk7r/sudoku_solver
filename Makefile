CC = gcc
CFLAGS = -Ofast -march=native -funroll-loops -ftree-vectorize -fopt-info-vec-optimized -O3 -Wall -Wextra -Werror
INCLUDES = -I./src

SRC_SEQ = src_seq/main.c src_seq/solver.c src_seq/sudoku_utils.c src_seq/helper_funcs.c
SRC_PAR = src_parallel/main_parallel.c src_parallel/solver_parallel.c src_parallel/sudoku_utils_parallel.c src_parallel/helper_funcs_parallel.c


# valgrind --tool=cachegrind --branch-sim=yes # for cache profiling - branch mispredicts
# valgrind --tool=cachegrind --cache-sim=yes

all: seq parallel

seq: $(SRC_SEQ)
	$(CC) -o seq $(SRC_SEQ) $(CFLAGS)

debug: $(SRC_SEQ)
	$(CC) -o seq $(SRC_SEQ) $(CFLAGS) -g

parallel: $(SRC_PARALLEL) 
	$(CC) -o parallel $(SRC_PAR) $(CFLAGS) -fopenmp

test: src/test_shii.c src/sudoku_utils.c src/helper_funcs.c
	$(CC) -o test src/test_shii.c src/sudoku_utils.c src/helper_funcs.c $(CFLAGS) $(INCLUDES)


# Cleans all executables and object files
clean:
	rm -f src/*.o main test src_parallel/*.o parallel


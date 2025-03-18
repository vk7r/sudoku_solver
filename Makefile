CC = gcc
CFLAGS = -Ofast -march=native -funroll-loops -ftree-vectorize -fopt-info-vec-optimized -O3 -Wall -Wextra -Werror
INCLUDES = -I./src

SRC_SEQ = src/seq/main.c src/seq/solver.c src/seq/sudoku_utils.c src/seq/helper_funcs.c
SRC_PAR = src/parallel/main_parallel.c src/parallel/solver_parallel.c src/parallel/sudoku_utils_parallel.c src/parallel/helper_funcs_parallel.c


# valgrind --tool=cachegrind --branch-sim=yes # for cache profiling - branch mispredicts
# valgrind --tool=cachegrind --cache-sim=yes

all: seq parallel

seq: $(SRC_SEQ)
	$(CC) -o seq $(SRC_SEQ) $(CFLAGS)

debug_seq: $(SRC_SEQ)
	$(CC) -o seq $(SRC_SEQ) $(CFLAGS) -g

debug_par : $(SRC_PAR)
	$(CC) -o par $(SRC_PAR) $(CFLAGS) -fopenmp -g

parallel: $(SRC_PARALLEL) 
	$(CC) -o par $(SRC_PAR) $(CFLAGS) -fopenmp

test: src/seq/test_shii.c src/seq/sudoku_utils.c src/seq/helper_funcs.c
	$(CC) -o test src/seq/test_shii.c src/seq/sudoku_utils.c src/seq/helper_funcs.c $(CFLAGS) $(INCLUDES)


# Cleans all executables and object files
clean:
	rm -f src/seq/*.o seq test src/parallel/*.o par


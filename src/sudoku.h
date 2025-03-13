#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

// Index structure
typedef struct
{
    unsigned char x;
    unsigned char y;
} Index_2D_t;


// Board structure (RxC)
typedef struct
{
    unsigned char **board;      // 2D array, ROWS x COLUMN
    unsigned char base;         // Base of the board
    unsigned char board_length; // Length of the board
    int tot_num_cells;    // Size of the board
    Index_2D_t *unAssignInd; // Array of unassigned indexes
    int N_unAssign;   // Number of unassigned indexes
} Board_t;

// sudoku_utils.c - FUNCTIONS
void destroy_board(Board_t *board);
bool DuplicateNumbersinRow(Board_t *board, int x);
bool DuplicateNumbersinCol(Board_t *board, int y);
bool DuplicateNumbersinBox(Board_t *board, int x, int y);
bool ValidateBoard(Board_t *board, int x, int y);
Board_t *init_board(unsigned char size);
Board_t *create_board_from_file(char *filename);


// solver.c - FUNCTIONS
bool solve(Board_t *board_struct, Index_2D_t *unAssignInd, int N_unAssign);

// helper_funcs.c - FUNCTIONS
void print_board(Board_t *board_struct);
double get_wall_seconds();

// test
void TestRowsForDuplicates(Board_t *board);
void TestColsForDuplicates(Board_t *board);
void TestBoxesForDuplicates(Board_t *board);
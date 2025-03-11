#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Index structure
typedef struct
{
    unsigned char x;
    unsigned char y;
} Index_2D;


// Board structure (RxC)
typedef struct
{
    unsigned char **board;      // 2D array, ROWS x COLUMN
    unsigned char base;         // Base of the board
    int board_size;   // Size of the board
    unsigned char board_length; // Length of the board
    Index_2D *unAssignInd; // Array of unassigned indexes
    unsigned char N_unAssign;   // Number of unassigned indexes
} Board;


// sudoku_utils.c - FUNCTIONS
void destroy_board(Board *board);
bool DuplicateNumbersinRow(Board *board, int x);
bool DuplicateNumbersinCol(Board *board, int y);
bool DuplicateNumbersinBox(Board *board, int x, int y);
bool ValidateBoard(Board *board, int x, int y);
Board *create_board_from_file(char *filename);

// helper_funcs.c - FUNCTIONS
void print_board(Board *board_struct);
Board *init_board(unsigned char size);
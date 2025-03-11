#include <stdbool.h> 
#include <stdio.h>


// PREFERABLY USE RxC
typedef struct {
    int **board; // 2D array, ROWS x COLUMN
    bool solvable; // Bool displaying if board is solvable
} Board;

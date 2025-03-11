#include "sudoku.h"


void print_board(Board *board_struct)
{
    int size = board_struct->board_size;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d  ", board_struct->board[i][j]);
        }
        printf("\n\n");
    }
}
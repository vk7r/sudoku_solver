#include "sudoku_parallel.h"

double get_wall_seconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
    return seconds;
}

void print_board(Board_t *board_struct)
{
    int size = board_struct->board_length;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d  ", board_struct->board[i * size + j]);
        }
        printf("\n\n");
    }
}

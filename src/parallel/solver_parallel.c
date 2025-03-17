#include "sudoku_parallel.h"

bool solve(Board_t *board_struct, Index_2D_t *unAssignInd, int N_unAssign, int n_threads)
{
    if (N_unAssign == 0) // No more empty positions, solution found
    {
        return true;
    }

    Index_2D_t index = unAssignInd[N_unAssign - 1];
    int x = index.x;
    int y = index.y;

    for (unsigned char val = 1; val <= board_struct->board_length; val++)
    {
        board_struct->board[x][y] = val; // Set guess
        // printf("guess: %d\n", val);
        if (ValidateBoard(board_struct, x, y))
        {
            // Solve recursively
            if (solve(board_struct, unAssignInd, N_unAssign - 1, n_threads))
            {
                return true;
            }
        }
    }
    board_struct->board[x][y] = 0; // No solution, reset value in backtracking
    return false;
}

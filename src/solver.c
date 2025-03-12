#include "sudoku.h"

bool solve(Board *board_struct, Index_2D *unAssignInd, unsigned char N_unAssign)
{
    if (N_unAssign == 0) // No more empty positions, solution found
    {
        return true;
    }

    Index_2D index = unAssignInd[N_unAssign - 1];
    int x = index.x;
    int y = index.y;

    for (unsigned char val = 1; val <= board_struct->board_size; val++)
    {
        board_struct->board[x][y] = val; // Set guess
        if (ValidateBoard(board_struct, x, y))
        {
            // Solve recursively
            if (solve(board_struct, unAssignInd, N_unAssign - 1))
            {
                return true;
            }
        }
    }
    board_struct->board[x][y] = 0; // No solution, reset value in backtracking
    return false;
}

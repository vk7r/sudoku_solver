#include "sudoku.h"

bool solve(Board *board_struct, int *unAssignInd, int N_unAssign, int BoardSize)
{
    char **board = board_struct->board;

    if (N_unAssign == 0) // No more empty position, solution found
    {
        return true;
    }

    int index = unAssignInd[N_unAssign - 1];
    int x = index / BoardSize;
    int y = index % BoardSize;

    for (int val = 1; val <= BoardSize; val++)
    {
        board[x][y] = val; // Set guess
        if (ValidateBoard(board_struct, x, y))
        {
            // Solve recursively
            if (solve(board_struct, unAssignInd, N_unAssign - 1, BoardSize))
            {
                return true;
            }
        }
    }
    board[x][y] = 0; // No solution, reset value in backtracking
    return false;
}
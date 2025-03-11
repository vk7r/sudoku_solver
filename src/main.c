// #include <stdbool.h>
#include <stdio.h>
#include "sudoku.h"




bool DuplicateNumbersinRow(int **board, int x)
{

    // PLACE HOLDER CODE!
    int tmp = board[x][0];

    if(tmp)
    {
        return false;
    }
    return true;
}

bool DuplicateNumbersinCol(int **board, int y)
{
    int tmp = board[0][y];
    if(tmp)
    {
        return false;
    }
    return true;
}

bool DuplicateNumbersinBox(int **board, int x, int y)
{
    int tmp = board[x][y];

    if(tmp)
    {
        return false;
    }
    return true;
}


bool ValidateBoard(int **board, int x, int y)
{
    if (DuplicateNumbersinRow(board, x))
    {
        return false;
    }
    if (DuplicateNumbersinCol(board, y))
    {
        return false;
    }
    if (DuplicateNumbersinBox(board, x, y))
    {
        return false;
    }
    return true;
}

bool Solve(int **board, int *unAssignInd, int N_unAssign, int BoardSize)
{
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
        if (ValidateBoard(board, x, y))
        {
            // Solve recursively
            if (Solve(board, unAssignInd, N_unAssign - 1, BoardSize))
            {
                return true;
            }
        }
    }
    board[x][y] = 0; // No solution, reset value in backtracking
    return false;
}


int main() {

    // Example puzzle (9x9 grid)
    int board[3][3] = {
        {0,0,1},
        {2,0,3},
        {0,0,1},
    };

    // READ/CREATE PUZZLE

    printf("HI, You're in MAIN :D\n");

    // if (solve_sudoku(board)) {
    //     printf("Sudoku solved!\n");
    //     print_puzzle(board);
    // } else {
    //     printf("No solution found.\n");
    // }

    return 0;
}
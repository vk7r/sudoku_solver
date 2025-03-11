#include "sudoku.h"

int main(int argv, char *argc) {

    if (argv != 2) {
        printf("Usage: ./sudoku <filename>\n");
        return 1;
    }
    // Example puzzle (3x3 grid)
    int board[3][3] = {
        0,0,1,
        2,0,3,
        0,0,1
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
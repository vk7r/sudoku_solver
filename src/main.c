#include "sudoku.h"

int main(int argv, char *argc[])
{

    // Check if the filename is passed as a command-line argument
    if (argv != 2)
    {
        printf("Usage: ./sudoku <filename>\n");
        return 1;
    }

    char *filename = argc[1];

    printf("HI, You're in MAIN :D\n");

    // Create the board from the file
    Board *board = create_board_from_file(filename);

    printf("board length: %d, n_unass: %d\n", board->board_length, board->N_unAssign);
    // Call the solve function with the necessary arguments from the board
    if (solve(board, board->unAssignInd, board->N_unAssign))
    {
        printf("Sudoku solved!\n");
        // print_board(board);
    }
    else
    {
        printf("No solution found.\n");
    }

    // Clean up and free memory
    destroy_board(board);

    return 0;
}

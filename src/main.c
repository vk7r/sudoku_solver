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

    double start_time = get_wall_seconds();
    // printf("HI, You're in MAIN :D\n");

    // Create the board from the file
    Board_t *board = create_board_from_file(filename);

    printf("board length: %d, n_unass: %d\n", board->board_length, board->N_unAssign);
    // Call the solve function with the necessary arguments from the board
    if (solve(board, board->unAssignInd, board->N_unAssign))
    {
        printf("Sudoku solved!\n");
        // print_board(board);
        
        double end_time = get_wall_seconds();
        printf("Time taken: %f seconds\n", end_time - start_time);
        // export_res_to_file(board, Filename);

        // printf("Double Checking Validity...\n");
        // for (int x = 0; x < board->board_length; x++)
        // {
        //     for (int y = 0; y < board->board_length; y++)
        //     {
        //         if (!ValidateBoard(board, x, y))
        //         {
        //             printf("Board is invalid!\n");
        //             return 1;
        //         }
        //     }
        // }
        // printf("Board is valid!\n");
    }
    else
    {
        printf("No solution found.\n");
    }

    // Clean up and free memory
    destroy_board(board);

    return 0;
}

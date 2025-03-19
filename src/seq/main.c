#include "sudoku.h"

int main(int argv, char *argc[])
{

    if (argv != 2)
    {
        printf("Usage: ./sudoku <filename>\n");
        return 1;
    }

    printf("Running Sequential Version...\n");
    
    char *filename = argc[1];

    double start_time = get_wall_seconds();

    // Create the board from the file
    Board_t *board = create_board_from_file(filename);

    printf("board length: %d, n_unass: %d\n\n", board->board_length, board->N_unAssign);

        if (solve(board, board->unAssignInd, board->N_unAssign))
        {
            printf("Sudoku solved!\n");
            
            double end_time = get_wall_seconds();
            printf("Time taken: %f seconds\n", end_time - start_time);
        }
        else
        {
            printf("No solution found.\n");
        }

    destroy_board(board);

    return 0;
}

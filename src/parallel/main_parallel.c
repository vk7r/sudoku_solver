#include "sudoku_parallel.h"

int main(int argv, char *argc[])
{

    // Check if the filename is passed as a command-line argument
    if (argv != 3)
    {
        printf("Usage: ./sudoku <filename> <n_threads>\n");
        return 1;
    }
    
    printf("Running Parrallel Version...\n");

    char *filename = argc[1];
    int n_threads = atoi(argc[2]);

    double start_time = get_wall_seconds();

    // Create the board from the file
    Board_t *board = create_board_from_file(filename);

    printf("board length: %d, n_unass: %d, n_threads: %d\n", board->board_length, board->N_unAssign, n_threads);
    // Call the solve function with the necessary arguments from the board

        if (solve(board, board->unAssignInd, board->N_unAssign, n_threads))
        {
            printf("Sudoku solved!\n");
            // print_board(board);
            
            double end_time = get_wall_seconds();
            printf("Time taken: %f seconds\n", end_time - start_time);
            // export_res_to_file(board, Filename);
        }
        else
        {
            printf("No solution found.\n");
        }

    // Clean up and free memory
    destroy_board(board);

    return 0;
}

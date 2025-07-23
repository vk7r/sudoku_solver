#include "sudoku_parallel.h"

int PAR_LIMIT;

int main(int argv, char *argc[])
{

    if (argv != 3)
    {
        printf("Usage: ./sudoku <filename> <n_threads>\n");
        return 1;
    }
    
    printf("Running Parallel Version...\n");
    
    char *filename = argc[1];
    int n_threads = atoi(argc[2]);


    // Create the board from the file
    Board_t *board = create_board_from_file(filename);
    
    // Magic number received from testing
    // PAR_LIMIT = board->N_unAssign - (4*board->tot_num_cells/100); //board->N_unAssign - 16; //n_threads; //(8*board->N_unAssign) / 10;
    
    // adjustikng the PAR_LIMIT as for a bigger board larger tasks are created
    if (board->board_length >= 50) {
        PAR_LIMIT = board->N_unAssign - (4 * board->tot_num_cells / 100);
    } else if (board->board_length >= 25) {
        PAR_LIMIT = board->N_unAssign - (2 * board->tot_num_cells / 100);
    } else {
        PAR_LIMIT = board->N_unAssign - (1 * board->tot_num_cells / 100);
    }

    printf("board length: %d, n_unass: %d, n_threads: %d, PAR_LIMIT: %d\n\n",
        board->board_length, board->N_unAssign, n_threads, PAR_LIMIT);
    
    double start_time = get_wall_seconds();

    #pragma omp parallel num_threads(n_threads)
    {
        #pragma omp single
        { 
            // will print out final board if solution is found from nested solve function
            if (solve(board, board->unAssignInd, board->N_unAssign))
            {
                printf("Sudoku solved!\n");
            }
            else
            {
                printf("No solution found.\n");
            }
        }
    }
    
    double end_time = get_wall_seconds();
    printf("%d Threads - solved in %f seconds\n",n_threads, end_time - start_time);

    destroy_board(board);

    return 0;
}

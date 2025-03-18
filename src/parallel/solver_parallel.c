#include "sudoku_parallel.h"

bool is_solved = false;

bool solve(Board_t *board_struct, Index_2D_t *unAssignInd, int N_unAssign)
{
    if (N_unAssign == 0) // No more empty positions, solution found
    {
        printf("Sudoku solved! by thread: %d\n", omp_get_thread_num());
        #pragma omp critical
        {
            // print_board(local_board);
            is_solved = true;
        }
        // print_board(board_struct);
        return true;
    }

    
    Index_2D_t index = unAssignInd[N_unAssign - 1];
    int x = index.x;
    int y = index.y;

    if (is_solved)
    {
        // printf("SOME OTHER SOLVED IT :D\n");
        return false;  // A solution is found somewhere --> break
    }

    for (unsigned char val = 1; val <= board_struct->board_length; val++)
    {
        #pragma omp task
        {
            // Board_t *local_board = (Board_t *)malloc(sizeof(Board_t));
            // memcpy(local_board, board_struct, sizeof(Board_t));
            Board_t *local_board = create_copy_of_board(board_struct);

            local_board->board[x][y] = val; // make guess
            // printf("Thread %d: x=%d, y=%d, guess=%d\n", omp_get_thread_num(), x, y, val);
            if (ValidateBoard(local_board, x, y))
            {
                // printf("GUESSING %d WAS CORRECT!\n", val);
                // printf(" %d - Board is valid... Trying new guess loop\n\n", omp_get_thread_num());
                solve(local_board, unAssignInd, N_unAssign - 1);
            }
            destroy_board(local_board);
        }
    }

    #pragma omp taskwait  // Wait for all tasks to complete
    return is_solved; // false if no solution found
}

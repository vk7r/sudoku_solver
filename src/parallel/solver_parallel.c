
#include "sudoku_parallel.h"

bool is_solved = false;

bool solve(Board_t *board_struct, Index_2D_t *unAssignInd, int N_unAssign)
{
    //#pragma omp cancellation point(taskgroup) // Check for found solution

    if (is_solved)
    {
        return false;  // A solution is found somewhere --> break
    }
  
    if (N_unAssign == 0) // No more empty positions, solution found
    {
        #pragma omp critical
        {
            //print_board(board_struct);
            is_solved = true;
        }
        //#pragma omp cancel taskgroup
        return true;
    }

    Index_2D_t index = unAssignInd[N_unAssign - 1];
    int x = index.x;
    int y = index.y;


    if (N_unAssign > PAR_LIMIT)
    {
        for (unsigned char val = 1; val <= board_struct->board_length; val++)
        {
            #pragma omp task firstprivate(val)
            {
                Board_t *local_board = create_copy_of_board(board_struct);

                local_board->board[x * local_board->board_length + y] = val; // make guess
                if (ValidateBoard(local_board, x, y))
                {
                    solve(local_board, unAssignInd, N_unAssign - 1);
                }
                destroy_board(local_board);
            }
        }
        #pragma omp taskwait  // Wait for all tasks to complete
        return is_solved;
    }
    else
    {
        // Sequential execution
        for (unsigned char val = 1; val <= board_struct->board_length; val++)
        {
            board_struct->board[x * board_struct->board_length + y] = val; // Set guess
            if (ValidateBoard(board_struct, x, y))
            {
                if (solve(board_struct, unAssignInd, N_unAssign - 1))
                {
                    return true;
                }
            }
        }
        board_struct->board[x * board_struct->board_length + y] = 0; // reset on backtrack
        return false;
    }
}

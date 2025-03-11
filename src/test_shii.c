#include "sudoku.h"

// Test duplicateNumbersInRow function for all rows:
int main()
{


    // Board *board = init_board(4);
    // board->base = 2;
    // int values[4][4] = {
    //     {0, 3, 1, 0},
    //     {2, 0, 3, 0},
    //     {0, 3, 1, 2},
    //     {3, 1, 0, 2}};

    Board *board = create_board_from_file("input_data/board_25x25.dat");

    // printf("BASE: %d\n", board->base);
    printf("Board - Base: %d, Size: %dx%d\n", board->base, board->base * board->base, board->base * board->base);
    // printf("unAssignInd: %d\n", board->unAssignInd[0]);
    printf("N_unAssign: %d\n", board->N_unAssign);
    // print_board(board);
    printf("\n");

    // Loop through all rows
    for (int num = 0; num < board->board_length; num++) 
    {
        if (DuplicateNumbersinRow(board, num))
        {
            printf("No duplicates in row %d\n", num + 1);
        }
        else
        {
            printf("Duplicates in row %d\n", num + 1);
        }
    }

    printf("\n");
    // Loop through all cols
    for (int num = 0; num < board->board_length; num++)
    {
        if (DuplicateNumbersinCol(board, num))
        {
            printf("No duplicates in col %d\n", num + 1);
        }
        else
        {
            printf("Duplicates in col %d\n", num + 1);
        }
    }


    // Clean up dynamically allocated memory
    destroy_board(board);

    return 0;
}

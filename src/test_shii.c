#include "sudoku.h"
#include <stdio.h>

// Function to test duplicates in all rows
void TestRowsForDuplicates(Board_t *board)
{
    printf("\nTesting for duplicates in rows:\n");
    for (int row_ind = 0; row_ind < board->board_length; row_ind++)
    {
        if (DuplicateNumbersinRow(board, row_ind))
        {
            printf("No duplicates in row %d\n", row_ind + 1);
        }
        else
        {
            printf("Duplicates in row %d\n", row_ind + 1);
        }
    }
}

// Function to test duplicates in all columns
void TestColsForDuplicates(Board_t *board)
{
    printf("\nTesting for duplicates in columns:\n");
    for (int col_ind = 0; col_ind < board->board_length; col_ind++)
    {
        if (DuplicateNumbersinCol(board, col_ind))
        {
            printf("No duplicates in col %d\n", col_ind + 1);
        }
        else
        {
            printf("Duplicates in col %d\n", col_ind + 1);
        }
    }
}

// Function to test duplicates in all boxes
void TestBoxesForDuplicates(Board_t *board)
{
    printf("\nTesting for duplicates in boxes:\n");
    int base = board->base; // Base size (subgrid size) of the board (e.g., 3 for 9x9, 4 for 16x16)

    // Loop through all boxes in the board
    for (int box_row = 0; box_row < base; box_row++)
    {
        for (int box_col = 0; box_col < base; box_col++)
        {

            // Calculate the top-left corner of the current box
            int box_start_x = box_row * base;
            int box_start_y = box_col * base;

            // Check for duplicates in this box
            if (DuplicateNumbersinBox(board, box_start_x, box_start_y))
            {
                printf("No duplicates in box (%d, %d)\n", box_row + 1, box_col + 1);
            }
            else
            {
                printf("Duplicates in box (%d, %d)\n", box_row + 1, box_col + 1);
            }
        }
    }
}

int main()
{
    // Create board from file or initialize manually
    Board_t *board = create_board_from_file("input_data/board_25x25.dat");

    // DOES NOT CURRENTLY WORK WHEN READING FROM A DAT FILE. [NEED TO FIX THIS]

    // Board *board = init_board(9);
    // board->base = 3;
    // board->board_length = 9;
    // board->N_unAssign = 10;

    // int values[9][9] = {
    //     {5, 3, 0, 0, 7, 0, 0, 0, 0},
    //     {6, 0, 1, 1, 9, 5, 0, 1, 1},
    //     {0, 9, 8, 0, 0, 1, 0, 6, 1},
    //     {8, 0, 0, 0, 6, 0, 0, 0, 1},
    //     {4, 0, 0, 8, 0, 3, 0, 0, 1},
    //     {7, 0, 0, 0, 2, 0, 0, 0, 1},
    //     {0, 6, 0, 0, 0, 0, 2, 8, 1},
    //     {0, 0, 0, 4, 1, 9, 0, 7, 1},
    //     {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    // printf("BOARD SIZE: %d\n", board->board_size);
    // for (int i = 0; i < board->board_length; i++)
    // {
    //     for (int j = 0; j < board->board_length; j++)
    //     {
    //         board->board[i][j] = values[i][j];
    //     }
    // }

    // Print basic information about the board
    printf("Board - Base: %d, Size: %dx%d\n", board->base, board->base * board->base, board->base * board->base);
    printf("N_unAssign: %d\n", board->N_unAssign);
    printf("\n");

    print_board(board);

    // Test duplicates in rows
    TestRowsForDuplicates(board);

    // Test duplicates in columns
    TestColsForDuplicates(board);

    // Test duplicates in boxes
    TestBoxesForDuplicates(board);

    // Clean up dynamically allocated memory
    destroy_board(board);

    return 0;
}

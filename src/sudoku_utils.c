#include "sudoku.h"

// ______________________ FREE FUNCTIONS ______________________
void destroy_board(Board *board)
{
    for (int i = 0; i < board->board_length; i++)
    {
        free(board->board[i]);
    }
    free(board->board);

    free(board->unAssignInd);

    free(board);
}

// ______________________ INTIALIZATION FUNCTIONS ______________________

// Initialize a board of size x size with all values set to 0
Board *init_board(unsigned char size)
{
    Board *board = (Board *)malloc(sizeof(Board));
    board->board_size = size;

    // Create a 2D array of size x size
    board->board = (unsigned char **)malloc(board->board_size * sizeof(unsigned char *));
    for (int i = 0; i < board->board_size; i++)
    {
        board->board[i] = (unsigned char *)malloc(board->board_size * sizeof(unsigned char));
    }

    return board;
}

// The first number form input_data is the base (e.g. 5) --> size 25x25
Board *create_board_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Board *new_board = (Board *)malloc(sizeof(Board));

    // Reads the first %d (int) from the file and stores it in new_board->board_size
    unsigned char base;
    fread(&base, sizeof(unsigned char), 1, file);

    unsigned char length;
    fread(&length, sizeof(unsigned char), 1, file);

    new_board->base = base;
    new_board->board_length = length;
    new_board->board_size = new_board->board_length * new_board->board_length;

    // Allocate memory for the 2D board array (board_length x board_length)
    new_board->board = malloc(new_board->board_length * sizeof(unsigned char *));

    // allocating memory for the unassigned indexes array
    new_board->unAssignInd = (Index_2D *)malloc(new_board->board_size * sizeof(Index_2D));
    new_board->N_unAssign = 0; // init to 0

    // Read the board data from the file
    for (int i = 0; i < new_board->board_length; i++)
    {
        // allocates each row of the 2D array for each iteration of the loop
        new_board->board[i] = (unsigned char *)malloc(new_board->board_length * sizeof(unsigned char));
        for (int j = 0; j < new_board->board_length; j++)
        {
            fread(&(new_board->board[i][j]), sizeof(char), 1, file);

            // Check if the current cell is unassigned --> add to unassigned indexes array and N_unAssign
            if (new_board->board[i][j] == 0)
            {
                new_board->unAssignInd[new_board->N_unAssign].x = i;
                new_board->unAssignInd[new_board->N_unAssign].y = j;
                new_board->N_unAssign++;
            }
        }
    }

    fclose(file);

    return new_board;
}


// ______________________ CHECK FUNCTIONS ______________________

bool DuplicateNumbersinRow(Board *board, int x)
{
    // printf("\n\n");
    // Bitmap solution...

    int size = board->board_length;
    // printf("INFUNC\n");
    // printf("Board - Base: %d, len: %d\n", board->base, board->board_length);
    // Array that keeps track of numbers seen in the row, each index represents a number
    bool seen[size];

    // Initialize seen array to false
    for (int i = 0; i < size; i++)
    {
        seen[i] = false;
    }

    // Loop through the row and check for duplicates
    for (int i = 0; i < size; i++)
    {
        unsigned char curr_num = board->board[x][i];
        if (curr_num != 0)
        {
            // printf("curr_num: %d, seen[%d]: %d\n", curr_num,curr_num-1, seen[curr_num - 1]);
            if (seen[curr_num - 1]) // if the number has been seen before
            {
                return false; // Duplicate found!
            }
            seen[curr_num - 1] = true;
        }
    }

    // for(int z = 0; z < size; z++)
    // {
    //     printf("seen[%d]: %d\n", z, seen[z]);
    // }
    return true;
}

bool DuplicateNumbersinCol(Board *board, int y)
{
    int size = board->board_length;

    // Array that keeps track of numbers seen in the row, each index represents a number
    bool seen[size];

    // Initialize seen array to false
    for (int i = 0; i < size; i++)
    {
        seen[i] = false;
    }

    // Loop through the row and check for duplicates
    for (int i = 0; i < size; i++)
    {
        unsigned char curr_num = board->board[i][y];

        if (curr_num != 0)
        {
            if (seen[curr_num - 1]) // if the number has been seen before
            {
                return false; // Duplicate found!
            }
            seen[curr_num - 1] = true;
        }
    }
    return true;
}

bool DuplicateNumbersinBox(Board *board, int x, int y)
{
    // board_length == amount of different numbers in each box
    int size = board->board_length;

    bool seen[size];
    for (int i = 0; i < size; i++)
    {
        seen[i] = false;
    }

    int box_size = board->base;
    // optimize division to make faster - or use of flag?
    // will truncate the decimal part to give correct index for the start of the box
    // e.g. for 3x3, 5/3 = 1, 1*3 = 3 (start of the box)
    int box_start_x = (x / box_size) * box_size; 
    int box_start_y = (y / box_size) * box_size;

    // Iterate over the box
    for (int i = 0; i < box_size; i++) // will iterate as many times as the box size
    {
        for (int j = 0; j < box_size; j++)
        {
            unsigned char curr_num = board->board[box_start_x + i][box_start_y + j];

            if (curr_num != 0)
            {                              
                if (seen[curr_num - 1])    
                    return false;          
                seen[curr_num - 1] = true; 
            }
        }
    }

    return true; // No duplicates found
}

bool ValidateBoard(Board *board, int x, int y)
{
    if (DuplicateNumbersinRow(board, x))
    {
        return false;
    }
    if (DuplicateNumbersinCol(board, y))
    {
        return false;
    }
    if (DuplicateNumbersinBox(board, x, y))
    {
        return false;
    }
    return true;
}
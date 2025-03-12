#include "sudoku.h"

// ______________________ FREE FUNCTIONS ______________________
void destroy_board(Board *board)
{
    for (int i = 0; i < board->board_length; i++)
    {
        free(board->board[i]);
    }
    free(board->board);

    if (board->unAssignInd != NULL)
    {
        free(board->unAssignInd);
    }
    free(board);
}

// ______________________ INTIALIZATION FUNCTIONS ______________________

// Initialize a board of size x size with all values set to 0
Board *init_board(unsigned char size)
{
    Board *board = (Board *)malloc(sizeof(Board));
    board->tot_num_cells = size;

    // Create a 2D array of size x size
    board->board = (unsigned char **)malloc(board->tot_num_cells * sizeof(unsigned char *));
    for (int i = 0; i < board->tot_num_cells; i++)
    {
        board->board[i] = (unsigned char *)malloc(board->tot_num_cells * sizeof(unsigned char));
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

    // Reads the first %d (int) from the file and stores it in new_board->tot_num_cells
    unsigned char base;
    if (fread(&base, sizeof(unsigned char), 1, file) != 1)
    {
        perror("Error reading base from file");
        exit(EXIT_FAILURE);
    }

    unsigned char length;
    if (fread(&length, sizeof(unsigned char), 1, file) != 1)
    {
        perror("Error reading length from file");
        exit(EXIT_FAILURE);
    }

    new_board->base = base;
    new_board->board_length = length;
    new_board->tot_num_cells = new_board->board_length * new_board->board_length;

    // Allocate memory for the 2D board array (board_length x board_length)
    new_board->board = malloc(new_board->board_length * sizeof(unsigned char *));

    // allocating memory for the unassigned indexes array
    new_board->unAssignInd = (Index_2D *)malloc(new_board->tot_num_cells * sizeof(Index_2D));
    new_board->N_unAssign = 0; // init to 0

    // Read the board data from the file
    for (int i = 0; i < new_board->board_length; i++)
    {
        // allocates each row of the 2D array for each iteration of the loop
        new_board->board[i] = (unsigned char *)malloc(new_board->board_length * sizeof(unsigned char));
        for (int j = 0; j < new_board->board_length; j++)
        {
            if (fread(&(new_board->board[i][j]), sizeof(char), 1, file) != 1)
            {
                perror("Error reading board data from file");
                exit(EXIT_FAILURE);
            }

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
    // Bitmap solution...

    int size = board->board_length;
    // printf("INFUNC\n");
    // printf("Board - Base: %d, len: %d\n", board->base, board->board_length);
    // Array that keeps track of numbers seen in the row, each index represents a number
    // bool *seen = (bool *)calloc(size, sizeof(bool));
    bool seen[size];
    memset(seen, 0, size);

    // Initialize seen array to false
    // for (int i = 0; i < size; i++)
    // {
    //     seen[i] = false;
    // }

    // Loop through the row and check for duplicates
    // printf("x: %d\n", x);
    for (int i = 0; i < size; i++)
    {
        unsigned char curr_num = board->board[x][i];
        if (curr_num != 0)
        {
            if (seen[curr_num - 1]) // if the number has been seen before
            {
                // printf("x: %d, i: %d\n", x, i);
                // printf("curr_num: %d, seen[%d]: %d\n", curr_num,curr_num-1, seen[curr_num - 1]);
                return true; // Duplicate found!
            }
            seen[curr_num - 1] = true;
        }
    }

    // for(int z = 0; z < size; z++)
    // {
    //     printf("seen[%d]: %d\n", z, seen[z]);
    // }
    // free(seen);
    return false;
}

bool DuplicateNumbersinCol(Board *board, int y)
{
    int size = board->board_length;

    // Array that keeps track of numbers seen in the row, each index represents a number
    // bool *seen = (bool *)calloc(size, sizeof(bool));
    bool seen[size];
    memset(seen, 0, size);

    // Initialize seen array to false
    // for (int i = 0; i < size; i++)
    // {
    //     seen[i] = false;
    // }

    // Loop through the row and check for duplicates
    for (int i = 0; i < size; i++)
    {
        unsigned char curr_num = board->board[i][y];

        if (curr_num != 0)
        {
            if (seen[curr_num - 1]) // if the number has been seen before
            {
                return true; // Duplicate found!
            }
            seen[curr_num - 1] = true;
        }
    }
    // free(seen);
    return false;
}

bool DuplicateNumbersinBox(Board *board, int x, int y)
{
    // board_length == amount of different numbers in each box
    int size = board->board_length;

    // bool *seen = (bool *)calloc(size, sizeof(bool));
    bool seen[size];
    memset(seen, 0, size);

    // for (int i = 0; i < size; i++)
    // {
    //     seen[i] = false;
    // }

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
                    return true;
                seen[curr_num - 1] = true;
            }
        }
    }

    // free(seen);
    return false; // No duplicates found
}

bool ValidateBoard(Board *board, int x, int y)
{
    // printf("Before checking validity: x = %d, board_length = %d\n", x, board->board_length);
    if (x < 0 || x >= board->board_length || y < 0 || y >= board->board_length)
    {
        printf("ERROR: Coordinates out of bounds (x=%d, y=%d, board_length=%d)\n",
               x, y, board->board_length);
        return false;
    }

    // printf("CHECKING VALIDITY WITH x: %d, y: %d\n", x, y);
    if (DuplicateNumbersinRow(board, x))
    {
        // printf("DEAD END: Duplicate in row\n");
        return false;
    }
    if (DuplicateNumbersinCol(board, y))
    {
        // printf("DEAD END: Duplicate in col\n");
        return false;
    }
    if (DuplicateNumbersinBox(board, x, y))
    {
        // printf("DEAD END: Duplicate in box\n");
        return false;
    }
    return true;
}
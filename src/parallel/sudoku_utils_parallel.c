#include "sudoku_parallel.h"

// ____________________________________________ FREE FUNCTIONS ____________________________________________
void destroy_board(Board_t *board)
{
    // Since board is now 1D, just free it once
    free(board->board);

    if (board->unAssignInd != NULL)
    {
        free(board->unAssignInd);
    }
    free(board);
}

// ____________________________________________ INTIALIZATION FUNCTIONS ____________________________________________

// Initialize a board of size x size with all values set to 0
Board_t *init_board(unsigned char size)
{
    Board_t *board = (Board_t *)malloc(sizeof(Board_t));
    board->tot_num_cells = size * size;
    board->board_length = size;

    // Create a 1D array of size*size
    board->board = (unsigned char *)malloc(board->tot_num_cells * sizeof(unsigned char));

    // Initialize all cells to 0
    memset(board->board, 0, board->tot_num_cells * sizeof(unsigned char));

    board->unAssignInd = NULL;
    board->N_unAssign = 0;

    return board;
}


Board_t* create_copy_of_board(Board_t *board_to_copy) {

    Board_t *new_board = (Board_t *)malloc(sizeof(Board_t));

    new_board->base = board_to_copy->base;
    new_board->board_length = board_to_copy->board_length;
    new_board->tot_num_cells = board_to_copy->tot_num_cells;
    new_board->N_unAssign = board_to_copy->N_unAssign;

    // Allocate 1D board array
    new_board->board = (unsigned char *)malloc(new_board->tot_num_cells * sizeof(unsigned char));
    memcpy(new_board->board, board_to_copy->board, new_board->tot_num_cells * sizeof(unsigned char));

    // Allocate and copy the unAssignInd array
    if (board_to_copy->N_unAssign > 0) 
    {
        new_board->unAssignInd = (Index_2D_t *)malloc(board_to_copy->N_unAssign * sizeof(Index_2D_t));
        memcpy(new_board->unAssignInd, board_to_copy->unAssignInd, board_to_copy->N_unAssign * sizeof(Index_2D_t));
    } 
    else
    {
        new_board->unAssignInd = NULL;
    }

    return new_board;
}


// The first number form input_data is the base (e.g. 5) --> size 25x25
Board_t *create_board_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Board_t *new_board = (Board_t *)malloc(sizeof(Board_t));

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
    new_board->tot_num_cells = length * length;

    // Allocate memory for the 1D board array (length * length)
    new_board->board = (unsigned char *)malloc(new_board->tot_num_cells * sizeof(unsigned char));

    // allocating memory for the unassigned indexes array
    new_board->unAssignInd = (Index_2D_t *)malloc(new_board->tot_num_cells * sizeof(Index_2D_t));
    new_board->N_unAssign = 0; // init to 0

    // Read the board data from the file
    for (int i = 0; i < new_board->board_length; i++)
    {
        for (int j = 0; j < new_board->board_length; j++)
        {
            if (fread(&(new_board->board[i * new_board->board_length + j]), sizeof(char), 1, file) != 1)
            {
                perror("Error reading board data from file");
                exit(EXIT_FAILURE);
            }

            // Check if the current cell is unassigned --> add to unassigned indexes array and N_unAssign
            if (new_board->board[i * new_board->board_length + j] == 0)
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

// ____________________________________________ CHECK FUNCTIONS ____________________________________________

inline bool DuplicateNumbersinRow(Board_t *board, int x)
{
    int size = board->board_length;
    bool seen[size];
    memset(seen, 0, size);

    for (int i = 0; i < size; i++)
    {
        unsigned char curr_num = board->board[x * size + i];
        if (curr_num != 0)
        {
            if (seen[curr_num - 1]) // if the number has been seen before
            {
                return true; // Duplicate found!
            }
            seen[curr_num - 1] = true;
        }
    }

    return false;
}

inline bool DuplicateNumbersinCol(Board_t *board, int y)
{
    int size = board->board_length;
    bool seen[size];
    memset(seen, 0, size);

    for (int i = 0; i < size; i++)
    {
        unsigned char curr_num = board->board[i * size + y];
        if (curr_num != 0)
        {
            if (seen[curr_num - 1])
            {
                return true;
            }
            seen[curr_num - 1] = true;
        }
    }
    return false;
}

inline bool DuplicateNumbersinBox(Board_t *board, int x, int y)
{
    int size = board->board_length;
    bool seen[size];
    memset(seen, 0, size);

    int box_size = board->base;

    int box_start_x = (x / box_size) * box_size;
    int box_start_y = (y / box_size) * box_size;

    for (int i = 0; i < box_size; i++)
    {
        for (int j = 0; j < box_size; j++)
        {
            unsigned char curr_num = board->board[(box_start_x + i) * size + (box_start_y + j)];
            if (curr_num != 0)
            {
                if (seen[curr_num - 1])
                    return true;
                seen[curr_num - 1] = true;
            }
        }
    }

    return false;
}

bool ValidateBoard(Board_t *board, int x, int y)
{
    if (x < 0 || x >= board->board_length || y < 0 || y >= board->board_length)
    {
        printf("ERROR: Coordinates out of bounds (x=%d, y=%d, board_length=%d)\n",
               x, y, board->board_length);
        return false;
    }

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

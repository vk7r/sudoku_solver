#!/bin/bash

TEST_COMMAND=".././par"
TEST_FILES=("../input_data/board_25x25.dat" "../input_data/board_36x36.dat" "../input_data/board_64x64.dat") 
RESULTS_FILE="par_results.txt"
THREAD_COUNTS=(2 4 8 16 32)

# Clear the results file at the start
echo "_____ PARALLEL TEST RESULTS _____" > $RESULTS_FILE

run_test() {
    local file=$1
    local threads=$2
    START_TIME=$(date +%s.%N)

    # Run the command but discard its output
    $TEST_COMMAND $file $threads > /dev/null 2>&1  
    END_TIME=$(date +%s.%N)

    # Calculate elapsed time
    ELAPSED_TIME=$(echo "$END_TIME - $START_TIME" | bc)

    # Append the formatted result to the file
    printf "%-10s - %0.4f seconds\n" "$threads threads" "$ELAPSED_TIME" >> $RESULTS_FILE
}

# Main Loop - iterate over test files and thread counts
echo "running parallel test..."
for file in "${TEST_FILES[@]}"; do
    # Extract board size from filename (e.g., "board_25x25.dat" → "25x25")
    BOARD_SIZE=$(echo "$file" | grep -oE '[0-9]+x[0-9]+')

    echo -e "\n__________ $BOARD_SIZE __________" >> $RESULTS_FILE

    for threads in "${THREAD_COUNTS[@]}"; do
        run_test "$file" "$threads"
    done
done

echo -e "All results saved in $RESULTS_FILE"

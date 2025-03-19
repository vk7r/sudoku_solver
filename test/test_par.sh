#!/bin/bash

TEST_COMMAND=".././par"
TEST_FILES=("../input_data/board_25x25.dat" "../input_data/board_36x36.dat" "../input_data/board_64x64.dat") 
RESULTS_FILE="par_results.txt"
THREAD_COUNTS=(2 4 6 8 12 16)
RUNS=10  # Number of times each test is repeated

# Clear the results file at the start
echo "_____ PARALLEL TEST RESULTS _____" > $RESULTS_FILE

run_test() {
    local file=$1
    local threads=$2
    local total_time=0

    for ((i=1; i<=RUNS; i++)); do
        START_TIME=$(date +%s.%N)
        $TEST_COMMAND $file $threads > /dev/null 2>&1  
        END_TIME=$(date +%s.%N)
        
        ELAPSED_TIME=$(echo "$END_TIME - $START_TIME" | bc)
        total_time=$(echo "$total_time + $ELAPSED_TIME" | bc)
    done

    # Calculate and format the average time
    AVG_TIME=$(echo "scale=4; $total_time / $RUNS" | bc)
    printf "%-10s - %0.4f seconds (avg over %d runs)\n" "$threads threads" "$AVG_TIME" "$RUNS" >> $RESULTS_FILE
}

# Main Loop - iterate over test files and thread counts
echo "running parallel test..."
for file in "${TEST_FILES[@]}"; do
    BOARD_SIZE=$(echo "$file" | grep -oE '[0-9]+x[0-9]+')

    echo -e "\n__________ $BOARD_SIZE __________" >> $RESULTS_FILE

    for threads in "${THREAD_COUNTS[@]}"; do
        run_test "$file" "$threads"
    done
done

echo -e "All results saved in $RESULTS_FILE"

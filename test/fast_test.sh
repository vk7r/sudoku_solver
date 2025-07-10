#!/bin/bash

# Usage: ./quick_test.sh <number_of_threads>

if [ $# -ne 1 ]; then
    echo "Usage: $0 <number_of_threads>"
    exit 1
fi

THREAD_COUNT=$1
TEST_COMMAND=".././par"
TEST_FILE="../input_data/board_36x36.dat"
RESULTS_FILE="par_quick_test.txt"
RUNS=1  # Run only once for speed

# Clear the results file
echo "_____ QUICK PARALLEL TEST _____" > $RESULTS_FILE

run_test() {
    local file=$1
    local threads=$2

    START_TIME=$(date +%s.%N)
    $TEST_COMMAND $file $threads > /dev/null 2>&1
    END_TIME=$(date +%s.%N)

    ELAPSED_TIME=$(echo "$END_TIME - $START_TIME" | bc)

    echo "$threads threads - $ELAPSED_TIME seconds" # >> $RESULTS_FILE
}


# Run the quick test
echo "Running $TEST_FILE with $THREAD_COUNT threads..."
run_test "$TEST_FILE" "$THREAD_COUNT"

echo "Result saved in $RESULTS_FILE"

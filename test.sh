#!/bin/bash

# Test Command and Files
TEST_COMMAND="./main"  # Assuming your compiled program is named "main"
TEST_FILES=("input_data/board_25x25.dat" "input_data/board_36x36.dat" "input_data/board_64x64.dat") 
RESULTS_FILE="results"

# Function to run the test with the given file
run_test() {
    local file=$1
    echo "Running test with input file: $file" >> $RESULTS_FILE
    $TEST_COMMAND $file >> $RESULTS_FILE 2>&1  # Append output to the results file (including errors)
}

# Function to check the result of the test
check_result() {
    if [ $? -eq 0 ]; then
        echo "Test passed!" >> $RESULTS_FILE
    else
        echo "Test failed!" >> $RESULTS_FILE
    fi
}

# Main
echo "Test Results:" > $RESULTS_FILE  # Start the results file with a header

for file in "${TEST_FILES[@]}"; do
    echo "========================================" >> $RESULTS_FILE
    run_test $file
    check_result
    echo "" >> $RESULTS_FILE  # Add a blank line for separation
done

echo "Results are saved in $RESULTS_FILE"

#!/bin/bash

TEST_COMMAND="./main"
TEST_FILES=("input_data/board_25x25.dat" "input_data/board_36x36.dat" "input_data/board_64x64.dat") 
RESULTS_FILE="results"


run_test() {
    local file=$1
    echo "Running test with input file: $file" >> $RESULTS_FILE
    $TEST_COMMAND $file >> $RESULTS_FILE 2>&1
}


check_result() {
    if [ $? -eq 0 ]; then
        echo "Test passed!" >> $RESULTS_FILE
    else
        echo "Test failed!" >> $RESULTS_FILE
    fi
}

# Main
echo "Test Results:" > $RESULTS_FILE

for file in "${TEST_FILES[@]}"; do
    echo "========================================" >> $RESULTS_FILE
    run_test $file
    check_result
    echo "" >> $RESULTS_FILE
done

echo "Results are saved in $RESULTS_FILE"

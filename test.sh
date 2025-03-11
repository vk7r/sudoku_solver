#!/bin/bash

TEST_FILE="test_file"
TEST_COMMAND="./test_command"

# Function to run the test
run_test() {
    echo "Running test..."
    $TEST_COMMAND $TEST_FILE
}


check_result() {
    if [ $? -eq 0 ]; then
        echo "Test passed!"
    else
        echo "Test failed!"
    fi
}

# Main
run_test
check_result

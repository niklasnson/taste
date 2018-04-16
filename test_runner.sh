#!/bin/bash
ITER=$(($1))
touch "output_$ITER.txt"
for ((i=1; i<=$1; i++)); do
    ./test_solutions.out | grep FAILED | grep -E -v "[):]$" | grep "^\[" >> "output_$ITER.txt"
    echo "[$i] Test done."
done
#!/bin/sh
# First number is the iteration, the rest array values.
tests=(
"2 1 2 3 4 5"
"3 1 2 3 4 5"
"3 15"
"1 1 2 3 4"
"20 1 2 3 4 5 6"
"2 32 45 43 23 54 23 54 34"
"0 32 45 43 23 54 23 54 34"
"3 3 234 25 345 45 34 234 235 345"
"4 3 234 25 345 45 34 234 235 345 34 534 45 645 645 645 4656 45 3"
"20 23 345 345 345 34536 567 568 6 34536 54 7546 456"
)
make;
for ((i = 0;  i < ${#tests[@]}; i++))
do
  echo "--- Test $i --- "
  ./list_adder ${tests[$i]}
done

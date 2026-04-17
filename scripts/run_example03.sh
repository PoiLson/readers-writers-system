#!/bin/bash
number=$(../build/open ../data/accounts50.bin)
echo "Shared Memory ID: $number"

../build/reader -f ../data/accounts50.bin -l 44 -d 5 -s "$number" &
../build/reader -f ../data/accounts50.bin -l 43[,45] -d 5 -s "$number" &
../build/reader -f ../data/accounts50.bin -l 4 -d 5 -s "$number" &

sleep 1

../build/writer -f ../data/accounts50.bin -l 35 -v 67 -d 4 -s "$number" &
../build/reader -f ../data/accounts50.bin -l 1 -d 5 -s "$number" &
../build/writer -f ../data/accounts50.bin -l 48 -v 67 -d 4 -s "$number" &

sleep 1

../build/writer -f ../data/accounts50.bin -l 17 -v 67 -d 4 -s "$number" &

sleep 1

../build/reader -f ../data/accounts50.bin -l 28 -d 5 -s "$number" &
../build/reader -f ../data/accounts50.bin -l 16 -d 5 -s "$number" &

sleep 1

../build/writer -f ../data/accounts50.bin -l 30 -v 67 -d 4 -s "$number" &

# Wait for all background jobs to finish
wait

../build/close "$number"  ../data/accounts50.bin

# Print a message indicating that all processes have completed
echo "All processes have completed."
#!/bin/bash
number=$(../build/open ../data/accounts50.bin)
echo "Shared Memory ID: $number"
# Execute writer commands with output redirection to both terminal and log files
../build/writer -f ../data/accounts50.bin -l 44 -v 67 -d 4 -s "$number" &
../build/writer -f ../data/accounts50.bin -l 44 -v -67 -d 4 -s "$number" &

sleep 1

# Execute reader commands with output redirection to both terminal and log files
../build/reader -f ../data/accounts50.bin -l 1[,4] -d 5 -s "$number" &

sleep 1

../build/writer -f ../data/accounts50.bin -l 7 -v 67 -d 3 -s "$number" &

sleep 1

../build/reader -f ../data/accounts50.bin -l 44 -d 4 -s "$number" &
../build/reader -f ../data/accounts50.bin -l 37 -d 5 -s "$number" &
../build/reader -f ../data/accounts50.bin -l 45 -d 5 -s "$number" &

../build/writer -f ../data/accounts50.bin -l 36 -v 67 -d 2 -s "$number" &
../build/writer -f ../data/accounts50.bin -l 18 -v 67 -d 2 -s "$number" &

# Wait for all background jobs to finish
wait

../build/close "$number"  ../data/accounts50.bin

# Print a message indicating that all processes have completed
echo "All processes have completed."
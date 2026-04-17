#!/bin/bash
number=$(../build/open ../data/accounts50.bin)
echo "Shared Memory ID: $number"


../build/reader -f ../data/accounts50.bin -l 34[,36] -d 5 -s "$number" &

sleep 1

../build/writer -f ./data/accounts50.bin -l 35 -v 67 -d 4 -s "$number" &

sleep 1

../build/writer -f ../data/accounts50.bin -l 48 -v 67 -d 4 -s "$number" &

sleep 1

../build/reader -f ../data/accounts50.bin -l 23 -d 5 -s "$number" &

sleep 1

../build/reader -f ../data/accounts50.bin -l 14 -d 5 -s "$number" &

sleep 1

../build/reader -f ../data/accounts50.bin -l 23[,26] -d 5 -s "$number" &

sleep 1

../build/writer -f ../data/accounts50.bin -l 12 -v 67 -d 4 -s "$number" &

sleep 1

../build/writer -f ../data/accounts50.bin -l 32 -v 67 -d 4 -s "$number" &

sleep 1

../build/reader -f ../data/accounts50.bin -l 24[,28] -d 5 -s "$number" &


# Wait for all background jobs to finish
wait

../build/close "$number"  ../data/accounts50.bin

# Print a message indicating that all processes have completed
echo "All processes have completed."
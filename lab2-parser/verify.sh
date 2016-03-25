#!bin/bash

if [ "g++ -g -Wall -std=c++11 *.cpp -o lab" ]; then
	echo "Compile complete"
	echo "Running tests..."
	
	for filename in /tests/in*; do
		./lab $filename "actual"
		if [ "diff "]
	done
fi
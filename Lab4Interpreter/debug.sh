#!/bin/bash
reset
if g++ -g -Wall -std=c++11 *.cpp -o lab; then
	echo "Compile complete"
	./lab "tests/in$1" "actual"
	diff "actual" "tests/out$1" && echo "Test '"$1"' passed"
fi

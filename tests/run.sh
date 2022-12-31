#!/bin/bash

IFS=$' '
files="single.txt simple.txt parentheses.txt parse-errors1.txt parse-errors2.txt parse-errors3.txt"

for file in $files
do
	echo "tests: $file"
	echo $'\n'
	IFS=$'\n'
	lines=$(cat $file)
	for line in $lines
	do
		echo "input: $line"
		echo "output: $(../eval $line)"
		echo $'\n'
	done
done

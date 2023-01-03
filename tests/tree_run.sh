#!/bin/bash

IFS=$' '
files="parentheses.txt"

for file in $files
do
	echo "tests: $file"
	echo $'\n'
	IFS=$'\n'
	lines=$(cat $file)
	for line in $lines
	do
		echo "input: $line"
		echo "output: $(../eval -p $line)"
		echo $'\n'
	done
done

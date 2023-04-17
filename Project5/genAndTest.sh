#!/bin/bash 
cmp studentOutput.txt profSolution.txt
until [ $? -ne 0 ]
do
./inputGen
./a.out < input.txt > studentOutput.txt
./project5_solution_linux_intel < input.txt > profSolution.txt
done
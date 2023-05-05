#!/bin/bash 
cmp studentOut.txt profOutput6.txt
until [ $? -ne 0 ]
do
./inputGen
./a.out < input.txt > studentOutput.txt
./project6_solution_linux_intel < input.txt > profSolution.txt
done
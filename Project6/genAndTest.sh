#!/bin/bash 
cmp studentOut.txt profOutput6.txt
until [ $? -ne 0 ]
do
./inputGen
./a.out < input.txt > studentOut.txt
./project6_solution_linux_intel < input.txt > profOutput6.txt
done
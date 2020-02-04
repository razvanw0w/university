#!/bin/bash
# count the number of lines for which the first and the second word are equal

grep "^\(\<\w\+\>\)\s\+\1.*$" lab.txt 

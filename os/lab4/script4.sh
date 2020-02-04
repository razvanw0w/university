#!/bin/bash
# count all lines which begin and end with the same word

grep "^\(\<\w\+\>\).*\1" lab.txt 

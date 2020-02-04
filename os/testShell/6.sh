#!/bin/bash

for file in `find -perm -o+w`
do
	ls -la $file | awk '{print $1 " " $9}'
	chmod o-w $file
	ls -la $file | awk '{print $1 " " $9}'
done

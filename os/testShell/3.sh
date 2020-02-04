#!/bin/bash

for file in `find -name "*.log"`
do
	sort $file > temp.txt
	mv temp.txt $file
done

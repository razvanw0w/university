#!/bin/bash

a=${1:-"ten"}

cat $a | while read fw l
do
	echo "First word: $fw ### Rest of the line: $l"
done

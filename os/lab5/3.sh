#!/bin/bash

for a in $@
do
	if test -f $a
	then
		echo "$a is a file"
	fi
done


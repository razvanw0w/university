#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Error: No arguments"
	exit 1
fi

for arg in $@
do
	if `! echo $arg | grep -q "[^a-zA-Z]"`
	then
		if `ls -la | grep -q " $arg$"`
		then
			echo "$arg is a file in the curr. directory"
		fi
	fi
done

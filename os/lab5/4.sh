#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Error: Please add at least one argument!"
	exit 1
fi

for a in $@
do
	if test -r $a
	then
		if file $a | grep -q "text"
		then
			echo $a		 
		fi
	fi
done | xargs wc -w | grep total | awk '{print $1}'

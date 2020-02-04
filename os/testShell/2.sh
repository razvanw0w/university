#!/bin/bash

foundFiles=0
for file in `find -name "*.c"`
do
	if [ $foundFiles -eq 2 ]
	then
		break
	fi
	if [ `cat $file | wc -l` -gt 500 ]
	then
		foundFiles=`expr $foundFiles + 1`
		echo $file
	fi
done

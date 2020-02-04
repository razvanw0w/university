#!/bin/bash

for user in `ps -ef | awk '{print $1}' | grep -v "UID" | sort | uniq`
do
	fullName=`finger $user | grep "Name" | grep -o " [^ ]\+*$"`
	numberOfProcesses=`ps -ef | grep "$user " | wc -l`
	echo "$fullName $numberOfProcesses"
done

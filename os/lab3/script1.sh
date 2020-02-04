#!/bin/bash

echo "Hello world"
echo "The number of arguments is: $#"
echo "The fifth argument is: $5"
echo "All the arguments: $@"
echo "Same thing as \$@ does: $*"

v="Test"
vv="Test1"

#echo "v: ${v}v"

for a in $@
do
	echo "a: ${a}"
	if test -f ${a}; then
		echo "$a represents a file"
		if [ -r ${a} ]; then
			echo "${a} is a readable file"
			if file ${a} | grep -q "text"; then
				echo "${a} is a readable text file"
			fi
		fi
	fi
done

#!/bin/bash

echo "The number of arguments is $#"
echo "All args: $*"

v=10
v1=11

a=${1:-"ten"}

echo "v:${v}"

echo "First arg: $a"

echo "sum: $((v+v1))"

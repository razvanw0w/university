#!/bin/bash
# sed 's#expr1#expr2#mod' lab.txt -> replace first occurence of expr1 with expr2
# sed 's#expr1#expr2#2' lab.txt -> replace second occurence of expr1 with expr2
# awk - $0 = whole line

awk '{if(index($1, $2)==1&&length($2)==length($1)){print $0}}' lab.txt

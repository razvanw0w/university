#!/bin/bash
# sed 's#expr1#expr2#mod' lab.txt -> replace first occurence of expr1 with expr2
# sed 's#expr1#expr2#2' lab.txt -> replace second occurence of expr1 with expr2

sed 's#\<b\w\+\>##2i' labcopy.txt

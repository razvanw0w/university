#!/bin/bash
# display all words starting with 'a'
# -o = display only the matching part i.e. the words

grep -oc "\<a\w*\>" lab.txt

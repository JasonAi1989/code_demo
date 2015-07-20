#!/bin/bash

BIN=/usr/bin/supn
string=$($BIN $@)

result=
for substr in $string
do
	if [ "${substr:0:1}" = "N" ]
	then
		substr="YUANV"
	fi
	
	result="$result $substr"
done

echo $result

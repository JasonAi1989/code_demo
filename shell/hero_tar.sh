#!/bin/bash

echo "Please input the file name"
read filename
if [ ! -n "$filename" ]
then
	exit;
fi

tar_file="$(pwd)/hero.tar.gz"
cat $filename | while read line
do
	if [ "${line:0:1}" != "[" ]
	then
		continue
	fi
	
	len=${#line}
	file=${line:1:len-2}
	
	echo "$file"
	if [ ! -e "$tar_file" ]
	then
		tar -cvf $tar_file $file
	else
		tar -rvf $tar_file $file
	fi
done

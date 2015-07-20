#! /bin/sh
ERR_MSG="miss the file "
file_path=$1
if [ ! -n "$file_path" ];then
    echo $ERR_MSG 
    exit
fi

file=${file_path##*/}
file_1=${file%.tar*}
file_2=${file%.tgz*}
file=${file_1:?$file_2}

if [ "$file_1" != "$file" ];then
    file=$file_1
else
    file=$file_2
fi
echo $file
echo $file_1
echo $file_2


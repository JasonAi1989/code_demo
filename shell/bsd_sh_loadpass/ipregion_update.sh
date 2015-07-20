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

new_file_path=`printf "/ca/conf/%s" "$file"`
echo $new_file_path

mv /ca/conf/ipregion /ca/conf/ipregion_bak
tar -zxvf $file_path -C /ca/conf

mv $new_file_path /ca/conf/ipregion

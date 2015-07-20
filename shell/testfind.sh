#!/bin/bash

func_catfile()
{
	local file=$1
	local len
	
	if [ "${file:0-1}" = "\\" ]
    then
        len=${#file}
        file="${file:0:len-1}"

        flag=1
    elif [ $flag -eq 1 ]
    then
        flag=2
    else
        flag=0
    fi

    case $flag in
        1)
            if [ -n "$extra_name" ]
            then
                extra_name="$extra_name $file"
            else
                extra_name="$file"
            fi
            return 0;;
        2)
            file="$extra_name $file"
            extra_name=
            flag=0;;
        *)
            ;;
    esac
	
	global_file=$file
	return 1
}

func_file_inexistent()
{
	local filelist=$(find $instead_path -type f|sed -e 's/ /\\ /g') 
	local file
	local log=$(pwd)/inexistent_log
	
	rm -rf $log
	
	for file in $filelist
	do	
		func_catfile $file
		if [ $? -eq 0 ]
		then
			continue
		fi
		
		file=$global_file
		
		if [ ! -e "$file" ]  #inexistent
		then
			echo "[$file]" | cat >> $log
		fi
	done
}

#####     main   #####
extra_name=
global_file=
flag=0

instead_path=$1

func_file_inexistent


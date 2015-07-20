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
func_compare()
{
	local file=$1
	local avo_arg
	local len
	local temp_str
	local bad_file=0
		
	for avo_arg in $avoid_path
	do
		len=${#avo_arg}
		temp_str=${file:len:1}
		if [ -n "$temp_str" ] && [ "$temp_str" != "/" ]
		then
			continue
		fi
			
		temp_str=${file:0:len}
		if [ "$temp_str" = "$avo_arg" ]
		then
			bad_file=1
			break
		fi
	done
	
	return $bad_file
}

func_rename_file()
{
	local src=$1
	local tar=$2
	local file
	local newfile
	
	local filelist=$(find $instead_path -name "*$src*" -type f)  #mv the files 
	for file in $filelist
	do
		func_compare $file
		if [ $? -eq 1 ]
		then
			continue
		fi
		
		echo $file
		newfile=$(echo $file | sed -e "s/$src/$tar/g")
		echo $newfile
		mv $file $newfile
	done

	filelist=$(find $instead_path -name "*$src*" -type d)  #mv the dir
	for file in $filelist
	do
		func_compare $file
		if [ $? -eq 1 ]
		then
			continue
		fi
			
		echo $file
		newfile=$(echo $file | sed -e "s/$src/$tar/g")
		echo $newfile
		mv $file $newfile
	done
}

func_change_context()
{
	local filelist=$(find $instead_path -type f|sed -e 's/ /\\ /g')  
	local file
	local bakfile
	
	for file in $filelist 
	do
		func_compare $file
		if [ $? -eq 1 ]
		then
			continue
		fi

		func_catfile $file
		if [ $? -eq 0 ]
		then
			continue
		else
			file=$global_file
		fi
		
##########		
#		if [ "${file:0-11}" != ".properties" ] # && [ "${file:0-4}" != ".pdf" ] && [ "${file:0-5}" != ".html" ]
#		if [ "${file:0-5}" != ".html" ]
#		then
#			continue
#		fi
##########

#	 echo $file
		#sed -i.ybak -e 's/niksun/yuanvi/g' -e 's/NIKSUN/YUANVI/g' -e 's/NETVCR/YUNAAS/g' -e 's/netvcr/yunaas/g' -e 's/nikos/yuanv/g' -e 's/NIKOS/YUANV/g' $file 
		#sed -i.ybak -e 'N;s/NIKSUN\n/YUANVI\n/g' "$file"
		sed -i.ybak -e 's/com.niksun.web.security.User/com.yuanvi.web.security.User/g' -e 's/com\/niksun\/web\/security\/User/com\/yuanvi\/web\/security\/User/g' "$file"
		bakfile=$file".ybak" 
		rm -rf "$bakfile"
#    echo $bakfile
	done
}

func_change_context_back()
{
	local filelist=$(find $instead_path -type f|sed -e 's/ /\\ /g') 
	local file
	local bakfile
	
	for file in $filelist 
	do
		func_compare $file
		if [ $? -eq 1 ]
		then
			continue
		fi
		
		func_catfile $file
		if [ $? -eq 0 ]
		then
			continue
		else
			file=$global_file
		fi	
		
#	 echo $file
		sed -i.ybak -e 's/yuanvi/niksun/g' -e 's/YUANVI/NIKSUN/g' -e 's/YUNAAS/NETVCR/g' -e 's/yunaas/netvcr/g' -e 's/yuanv/nikos/g' -e 's/YUANV/NIKOS/g' "$file"
		bakfile=$file".ybak" 
		rm -rf "$bakfile"
#    echo $bakfile
	done
}

func_forward()
{
	#modify the file name
	func_rename_file "niksun" "yuanvi"
	func_rename_file "niksun" "yuanvi"
	func_rename_file "NIKSUN" "YUANVI"
	func_rename_file "NIKSUN" "YUANVI"

	func_rename_file "NETVCR" "YUNAAS"
	func_rename_file "NETVCR" "YUNAAS"
	func_rename_file "netvcr" "yunaas"
	func_rename_file "netvcr" "yunaas"

	func_rename_file "nikos" "yuanv"
	func_rename_file "nikos" "yuanv"
	func_rename_file "NIKOS" "YUANV"
	func_rename_file "NIKOS" "YUANV"

	#modify the file context	
	func_change_context 
}

func_back()
{
	#modify the file name
	func_rename_file  "yuanvi" "niksun" 
	func_rename_file  "yuanvi" "niksun" 
	func_rename_file  "YUANVI" "NIKSUN" 
	func_rename_file  "YUANVI" "NIKSUN" 

	func_rename_file  "YUNAAS" "NETVCR" 
	func_rename_file  "YUNAAS" "NETVCR" 
	func_rename_file  "yunaas" "netvcr" 
	func_rename_file  "yunaas" "netvcr" 

	func_rename_file  "yuanv" "nikos" 
	func_rename_file  "yuanv" "nikos" 
	func_rename_file  "YUANV" "NIKOS" 
	func_rename_file  "YUANV" "NIKOS" 

	#modify the file context
	func_change_context_back
}

func_show()
{
	local log=$(pwd)/log
	local filelist=$(find $instead_path -type f|sed -e 's/ /\\ /g') 
	local file
	local string
	
	rm -rf $log
	
	for file in $filelist 
	do
		func_compare $file
		if [ $? -eq 1 ]
		then
			continue
		fi
		
		func_catfile $file
		if [ $? -eq 0 ]
		then
			continue			
		else
			file=$global_file
		fi
		
##########		
#		if [ "${file:0-11}" != ".properties" ] && [ "${file:0-4}" != ".pdf" ] && [ "${file:0-5}" != ".html" ]
#		if [ "${file:0-4}" != ".jar" ]
#		if [ "${file:0-11}" = ".properties" ] || [ "${file:0-4}" = ".pdf" ] || [ "${file:0-5}" = ".html" ] \
#		   || [ "${file:0-4}" = ".jar" ] || [ "${file:0-4}" = ".jsp" ] || [ "${file:0-4}" = ".xml" ]  \
#		   || [ "${file:0-3}" = ".sh" ] || [ "${file:0-6}" = ".class" ] #|| [ "${file:0-5}" = ".java" ]
#		if [ "${file:0-5}" != ".html" ]
#		then
#			continue
#		fi
##########
		
		case $1 in
			niksun)
				#string=$(sed -n -e '/niksun/p' -e '/NIKSUN/p' -e '/NETVCR/p' -e '/netvcr/p' -e '/nikos/p' -e '/NIKOS/p' "$file" );;
				#string=$(sed -n  -e '/niksun /p' -e '/NIKSUN /p' -e 'N;/niksun\n/p' -e 'N;/NIKSUN\n/p' "$file" );;  
				#string=$(sed -n  -e 'N;/NIKSUN\n/p'  "$file" );;  
				string=$(sed -n  -e '/niksun/p' -e '/NIKSUN/p'  "$file" );;  
			yuanvi)
				#string=$(sed -n -e '/yuanvi/p' -e '/YUANVI/p' -e '/YUNAAS/p' -e '/yunaas/p' -e '/yuanv/p' -e '/YUANV/p' $file );;
				string=$(sed -n  -e '/YUANV/p' "$file" );;
			special)
				#string=$(sed -n  -e '/com.niksun.services/p' "$file" );;
				string=$(sed -n  -e '/com.niksun.services.web.dashboard.DashboardDataService/p' "$file" );;
			*)
				string=;;
		esac

		if [ -n "$string" ]
		then
			echo "[$file]" | cat >> $log
			echo "$string" | cat >> $log
			echo " " | cat >> $log
		fi
	done
}

func_file_inexistent()
{
	local filelist=$(find $instead_path -type f|sed -e 's/ /\\ /g') 
	local file
	local log=$(pwd)/inexistent_log
	
	rm -rf $log
	
	for file in $filelist
	do
		func_compare $file
		if [ $? -eq 1 ]
		then
			continue
		fi
		
		func_catfile $file
		if [ $? -eq 0 ]
		then
			continue
		else
			file=$global_file
		fi
		
		if [ ! -e "$file" ]  #inexistent
		then
			echo "[$file]" | cat >> $log
		fi
	done
}
##############   main     ###########

#####for func_catfile
flag=0
global_file=
extra_name=
#########

arg_num=$#
if [ $arg_num -lt 1 ]
then
	echo "arg num error"
	exit
fi

args=$*
instead_path=$1
path=$(pwd)

len=${#instead_path}
avoid_path="${args:$len+1}"

if [ -n $avoid_path ] #avoid_path = NULL
then
	avoid_path="$path"
else
	avoid_path="$avoid_path $path"
fi

avoid_path="$avoid_path /proc"

echo "instead path:$instead_path"
echo "avoid path:$avoid_path"

echo "Right? [YES]/NO"
read ret
case $ret in
no|No|NO|n|N) exit;;
esac

while true
do
	echo "Select the function:"
	echo "#1.from niksun to yuanvi"
	echo "#2.from yuanvi to niksun"
	echo "3.show niksun in file"
	echo "#4.show yuanvi in file"
	echo "5.only modify the context, from niksun to yuanvi"
	echo "#6.show inexistent files"
	echo "#7.show special"
	read ret
	case $ret in
	1)
		func_forward
		exit;;
	2)
		func_back
		exit;;
	3)
		func_show "niksun"
		exit;;
	4)
		func_show "yuanvi"
		exit;;
	5)
		func_change_context
		exit;;
	6)
		func_file_inexistent
		exit;;
	7)
		func_show "special"
		exit;;
	*)
		echo "Error number, please input again!"
	esac
done

exit







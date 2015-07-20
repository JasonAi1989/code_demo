#!/bin/sh   
list_alldir(){   
    for file in `ls -a $1`   
    do   
        if [ x"$file" != x"." -a x"$file" != x".." ]
        then   
            if [ -d "$1/$file" ]
            then   
                list_alldir "$1/$file"  
            else
		mv $2/$file $3/$file
		echo "mv $2/$file $3/$file"

		cp -f $1/$file $2/$file
                echo "cp -f $1/$file $2/$file" 
            fi   
        fi   
    done   
}   
 
mkdir_bak(){
if [ ! -f "$1" ]
then
    rm -rf $1
    echo "rm -rf $1"
fi
    mkdir $1
    echo "mkdir $1"
}

srcdir=/usr/src/release/nodebug/ca/bin
tardir=/ca/bin
bakdir=/ca/bin/cp_bak

mkdir_bak $bakdir
list_alldir $srcdir $tardir $bakdir

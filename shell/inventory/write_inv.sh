#!/bin/sh

flag=$1

#write mode
if [ "$flag" == "w" ]
then
    offset=$2
    file=$3

    val_list=$(cat $file)

    for val in $val_list
    do
        offset_hex=`echo "obase=16;$offset"|bc`
        hwm run eeprom -w -o $offset_hex -v $val
        echo "hwm run eeprom -w -o $offset_hex -v $val"
        let "offset += 1"
    done

#clean mode
elif [ "$flag" == "c" ]
then
    offset=$2
    len=$3
    echo "clean from $offset, length $len"
    while [ 1 ]
    do
        offset_hex=`echo "obase=16;$offset"|bc`
        hwm run eeprom -w -o $offset_hex -v 0xff
        echo "hwm run eeprom -w -o $offset_hex -v 0xff"
        let "offset += 1"
        if [ $offset -eq $len ]
        then
            break
        fi
    done
fi

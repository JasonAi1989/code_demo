#!/bin/bash

func_statistics()
{
    local value=$1
#    echo $value

    case $value in
        "211.88.25.110") let v1++;;
        "211.88.25.112") let v2++;;
        "211.88.25.114") let v3++;;
        "211.88.25.109") let v4++;;
    esac
}
#############
URL="http://211.88.25.226"
KEY="loadpass211.88.25"

v1=0
v2=0
v3=0
v4=0

for (( i = 1 ; $i <= 100; i++ ))
do
    string=$(curl -s $URL | sed -n /$KEY/p)
#    echo $string

    string=${string#*loadpass}
#    echo $string

    string=${string%%\"*}
#    echo $string

    func_statistics $string
    sleep 0.1
done

echo "statistics:"
echo "211.88.25.110: $v1"
echo "211.88.25.112: $v2"
echo "211.88.25.114: $v3"
echo "211.88.25.109: $v4"

exit

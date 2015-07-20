#!/bin/sh

#echo "123"

string=$(sockstat | grep ospfd | grep tcp4)
#echo $string 

substring=${string#*:}
port=$(echo $substring | sed 's/*:*/ /g') 
#echo "port is "$port

if [ ! -n "$1" ] ;then 
    echo "you don't have input arg"
    exit 
fi

command="show ip ospf $1"
#echo $command
(sleep 0.1; echo "zebra"; sleep 0.1; echo "enable"; sleep 0.1; echo $command; sleep 0.1)|telnet 127.0.0.1  $port

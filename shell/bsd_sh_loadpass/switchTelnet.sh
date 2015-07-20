#!/bin/sh

flag=$1
file="/etc/inetd.conf"

#####check the arg
if [ ! -n "$flag" ];then
    echo "please input on/off" 
    exit
fi

#####turn on/off
val=$(sed -n "/#telnet/p" $file)
#echo "$val"

if [ "$flag" = "on" ];then
    if [ -n "$val" ];then
        sed -i.bak 's/#telnet/telnet/' $file 
    fi
        echo "on"
else
    if [ ! -n "$val" ];then
        sed -i.bak 's/telnet/#telnet/' $file 
    fi
        echo "off"
fi

#####restart/start the inetd process
my_val=$(ps -aux | grep inetd | sed 'N;s/\n/ /g' | sed -n 's/[^0-9]*\([0-9]*\).*/\1/p')
echo "old pid is $my_val"
kill -9 $my_val
/usr/sbin/inetd -wW
my_val=$(ps -aux | grep inetd | sed 'N;s/\n/ /g' | sed -n 's/[^0-9]*\([0-9]*\).*/\1/p')
echo "new pid is $my_val"

#!/bin/bash

arg_num=$#
args=$*

if [ $arg_num -eq 0 ]
then
    echo "please input the process which you want to kill!"
    exit
fi

self_pid=$$

for i in $args
do
    pid=$(ps -aux|grep \[${i:0:1}]${i:1} | sed -n 's/[^0-9]*\([0-9]*\).*/\1/p') 

    for pid_i in $pid
    do
        if [ $self_pid -eq $pid_i ]
        then
            continue
        fi

        kill -9 $pid_i
    done
done


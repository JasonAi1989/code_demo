#!/bin/bash

cpu_max=100     # 100%
waittime=60 #second

while true
do
    pid=$(ps -aux|grep \[p]2pserver |awk '{print $2}')
    cpu_value=$(ps -aux|grep \[p]2pserver |awk '{print $3}')
    cpu_value=${cpu_value%.*}

    echo "pid $pid | cpu $cpu_value"

    if [ $cpu_value -ge $cpu_max ]
    then
        kill -9 $pid
    fi

    sleep $waittime
done



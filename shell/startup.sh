#!/bin/bash

while true
do
    ret=$(ps -aux|grep \[p]2pserver)
#    echo $ret
    if [ ! -n "$ret" ]
    then
        ./p2pserver
    fi

    sleep 2
done

#!/bin/bash

while true
do
    pid=$(ps -aux|grep \[a]pache2)
#    echo $pid
    if [ ! -n "$pid" ]
    then
#        echo "restart!!!"
        /etc/init.d/apache2 start
    fi

    sleep 1
done


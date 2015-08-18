#!/bin/bash

clear
echo "start"

./doubleProcess.sh &

echo "has start"
while ( true )
do
    pid=$(pgrep -f doubleProcess.sh)
    if [ -n "$pid" ]
    then
        printf "\b"
        printf "please wait\n"
        sleep 2
    else
        exit
    fi
done

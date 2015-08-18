#!/bin/bash

cpu_max=90    # 90%
waittime=5*60 #5 min

while true
do
    values=$(ps aux |awk '{print $2"@"$3}')
    for value in $values
    do
        pid=${value%@*}
        cpu_value=${value#*@}
        cpu_value=${cpu_value%.*}

        if [ "$cpu_value" = "%CPU" ]
        then
            continue
        fi

#        echo "pid $pid | cpu $cpu_value"
        if [ $cpu_value -ge $cpu_max ]
        then
            echo "pid $pid | cpu $cpu_value"
            kill -9 $pid
        fi
    done

    sleep $waittime
done



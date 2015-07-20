#!/bin/bash

cpu_max=100     # 100%
waittime=60 #second

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
			string=$(ps aux |grep $pid)
			echo "pid $pid | cpu $cpu_value | string[$string]"
            kill -9 $pid
        fi
    done

    sleep $waittime
done



#! /bin/sh

show()
{
	flag=0
	days=0
	time=30
	record=0

	val=$(ps -ax | grep \[/]ca/bin/logserver)
#	echo $val
	for single in $val
	do
		if [ "$single" = "/ca/bin/logserver" ];then
			record=$(($record+1))
		fi
        done
	if [ $record -lt 2 ];then
		echo "logserver stop"
		return
	fi

	val=$(ps -ax | grep \[/]ca/bin/logserver | sed -n '1p')
#	echo $val
	for single in $val
	do
		if [ $flag = 2 ];then
			time=$single
		fi
    
		if [ $flag = 1 ];then
			days=$single
			flag=2
		fi

		if [ "$single" = "/ca/bin/logserver" ];then
			flag=1
		fi
	done
	echo "logserver start"
	echo "days:$days    time:$time"
}

start()
{
	days=$1
	time=$2
#    echo "start"
	/ca/bin/logserver $days $time & 
}

stop()
{
#    echo "stop"
    my_val=$(ps -aux | grep "/ca/bin/logserver" | sed -n 's/[^0-9]*\([0-9]*\).*/\1/p')
#    echo $my_val
    for pid in $my_val 
    do
#  	echo "pid $pid"
	kill -9 $pid
    done
}

cmd=$1

if [ "$cmd" = "start" ];then
	stop
	start $2 $3
	sleep 0.2
	show
elif [ "$cmd" = "stop" ];then
	stop
	show
elif [ "$cmd" = "show" ];then
	show
else
    	echo "bad command"
fi

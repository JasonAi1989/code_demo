#!/bin/sh
###log check
###arg1 [days]  valid log days,
###arg2 [time]  the period of checking disk

func_check_days()
{
	if [ $days -eq 0 ]
	then
		return
	fi
	
	count=$days
	
	for file in $fileList
	do 
		if [ $count -eq 0 ]
		then 
			rm $file
			count=1
		fi
		
		count=$(( $count - 1 ))
	done
}

func_del_oldest_log()
{
	oldest=$(ls -rt $LOG_PATH/*.log | head -n 1)
#	echo "oldest: $oldest"
	
	rm $oldest
}

func_check_disk()
{
	while true
	do
		capacity=$(df /var | awk '{print $5}' | sed -n '/%/p' | sed 's/%//g')
		space=$(( 100 - $capacity ))
#		echo "$space"
		
		if [ $space -lt 20 ]
		then
			func_del_oldest_log
		else
			return
		fi
	done	
}

###########  main  ###############
LOG_PATH="/var/log/logserver"

if [ ! -e $LOG_PATH ]
then
	mkdir $LOG_PATH
fi

days=$1
time=$2

if [ -z $days ] || [ $days -lt 0 ]
then 
	days=0
fi

if [ -z $time ] || [ $time -lt 0 ]
then
	time=30 #minute
fi

#echo "days:$days, time:$time"

time=$(( $time * 60 ))  #second

while true
do
	fileList=$(ls -t $LOG_PATH/*.log)
#	echo "$fileList"
	
	func_check_days
	
	func_check_disk
	
	sleep $time
done

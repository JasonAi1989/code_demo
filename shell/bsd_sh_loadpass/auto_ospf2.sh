#!/bin/sh

##This shell scrip is used for command "router ospf", 
##to execute some command of ospf process
##Add by Jason Ai, 2016-4-18

#args:
#	$1: level string ENABLE_LE|CONFIG_LE|ROUTER_LE|CLEAR_LE
#	$2: command string, catted by #
##main##

#check
if [ "$#" != "2" ]
then
	echo "args number is error, please input [level] [command]"
	exit
fi

#get args
level=$1
initial_command=$2
command=$(echo $2 | sed "s/#/ /g")

inerface=${initial_command%%#*}

#echo "command: $command"
#dumex
case $level in
"ENABLE_LE")
	#echo "ENABLE_LE"
	(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable";sleep 0.01; echo $command; sleep 0.01; echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
	exit;;
"CONFIG_LE")
	#for interface command
	if [ "$inerface" = "interface" ]
	then
		temp=${initial_command%%@*}
		command1=$(echo $temp | sed "s/#/ /g")
		
		temp=${initial_command#*@}
		command2=$(echo $temp | sed "s/#/ /g")
		(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable"; sleep 0.01; echo "con t"; sleep 0.01; echo $command1; sleep 0.01; echo $command2; sleep 0.01; echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
	else
		#echo "CONFIG_LE"
		(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable"; sleep 0.01; echo "con t"; sleep 0.01; echo $command; sleep 0.01; echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
	fi
	exit;;
"ROUTER_LE")
	#echo "ROUTER_LE"
	(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable"; sleep 0.01; echo "con t"; sleep 0.01; echo "router ospf"; sleep 0.01; echo $command; sleep 0.01; echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
	exit;;
"CLEAR_LE")
	prefix=$(echo $command|awk '{print $1,$2}')
	#echo "CLEAR_LE"
	if [ "$command" = "clear network" ]
	then
		networklist=$(sed -n "/network/p" /vload/etc/ospf.conf | sed 's/ /#/g')
		for net_val in $networklist
		do
			net_val=$(echo $net_val | sed 's/#/ /g')
			command="no $net_val"
			(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable"; sleep 0.01; echo "con t"; sleep 0.01; echo "router ospf"; sleep 0.01; echo $command; sleep 0.01; echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
		done
	elif [ "$prefix" = "clear interface" ]
	then
		newcommand=$(echo $command | awk '{print $2,$3}')
		
		# delete the authentication-key/dead-interval/hello-interval/network/priority/retransmit-interval/transmit-delay
		(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable"; sleep 0.01; echo "con t"; sleep 0.01; \
		echo $newcommand; sleep 0.01; echo "no ospf authentication-key"; sleep 0.01; \
		echo "no ospf dead-interval"; sleep 0.01; echo "no ospf hello-interval"; sleep 0.01; \
		echo "no ospf network"; sleep 0.01; echo "no ospf priority"; sleep 0.01; \
		echo "no ospf retransmit-interval"; sleep 0.01; echo "no ospf transmit-delay"; sleep 0.01; \
		echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
		
		# delete the cost value
		costlist=$(cat /vload/etc/ospf.conf | sed -n '/cost/p' | awk '{print "no "$1,$2,$3,$5}' | sed 's/ /#/g')
		for nocommand in $costlist
		do
			nocommand=$(echo $nocommand | sed 's/#/ /g')
			(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable"; sleep 0.01; echo "con t"; sleep 0.01; echo $newcommand; sleep 0.01; echo $nocommand; sleep 0.01; echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
		done
		
		# delete the message-digest-key value
		meskeylist=$(cat /vload/etc/ospf.conf | sed -n '/message-digest-key/p' | awk '{print "no "$1,$2,$3,$4}' | sed 's/ /#/g')
		for nocommand in $meskeylist
		do
			nocommand=$(echo $nocommand | sed 's/#/ /g')
			(sleep 0.1; echo "zebra"; sleep 0.01; echo "enable"; sleep 0.01; echo "con t"; sleep 0.01; echo $newcommand; sleep 0.01; echo $nocommand; sleep 0.01; echo "write file"; sleep 0.01)|telnet 127.0.0.1  2604
		done		
	fi
	exit;;
esac

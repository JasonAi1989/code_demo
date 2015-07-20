#!/bin/sh
##backup the ca/bin files and the kernel

backup_func()
{
	if [ ! -d "$api" ]; then
		mkdir -p $api
	fi
	
	if [ ! -d "$kernel" ]; then
		mkdir -p $kernel
	fi	
	
	cp -f /kernel/GFAkernel $kernel
	cp -rf /ca/bin/* $api
}

recover_func()
{
	if [ ! -d "$api" ]; then
	else
		cp -rf $api/* /ca/bin/ 
	fi

	if [ ! -d "$kernel" ]; then
	else
	cp -f $kernel/kernel /kernel/GFAkernel 
	fi
}

backup=/root/backup
api=$backup/api
kernel=$backup/kernel

if [ ! -n "$1" ] ;then
    echo "you don't have input arg:backup or recover"
    exit
fi

if [ "$1" = "backup" ] ; then
	backup_func
	echo "backup ok"
	exit
fi

if [ "$1" = "recover" ] ; then
	recover_func
	echo "recover ok"
	exit
fi

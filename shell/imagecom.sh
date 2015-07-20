#!/bin/sh

func_on()
{
	 ret=$(sysctl net.inet.eccomtcp.rewrite_jpeg=1)
}

func_off()
{
	 ret=$(sysctl net.inet.eccomtcp.rewrite_jpeg=0)
}

func_quality()
{
	 ret=$(sysctl net.inet.eccomtcp.jpeg_quality=$value)
}

func_show()
{
	 ret=$(sysctl net.inet.eccomtcp.rewrite_jpeg | awk '{print $2}')
	if [ "$ret" = "1" ]
	then
		echo "jpeg compression state: on"
	else
		echo "jpeg compression state: off"
	fi

	
	ret=$(sysctl net.inet.eccomtcp.jpeg_quality | awk '{print $2}')
	echo "jpeg compression quality: $ret"
}

if [ -z $1 ]
then
	echo "imagecom on/off/quality [value]/show"
fi

if [ "$1" = "on" ]
then
	func_on
	exit
fi

if [ "$1" = "off" ]
then
	func_off
	exit
fi

if [ "$1" = "quality" ]
then
	value=$2  #[1, 100]
	func_quality
	exit
fi

if [ "$1" = "show" ]
then
	func_show
	exit
fi

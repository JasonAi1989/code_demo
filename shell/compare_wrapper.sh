#!/bin/sh

kernelW="/usr/src/sys/eccom/app/proxy/kernelWrapper.c"
userW="/usr/src/kernelapi/lib/userWrapper.c"
kernel_temp="/var/kernel_temp"
user_temp="/var/user_temp"

if [ ! -n "$kernelW" ] || [ ! -n "$userW" ]
then
	echo "files are absent"
	exit
fi

ret1=$(sed -n "/Function/p" $kernelW)
ret2=$(sed -n "/Function/p" $userW)

echo ret1 > $kernel_temp
echo ret2 > $user_temp

ret3=$(diff $kernel_temp $kernel_temp)
echo "diff result:"
echo "$ret3"


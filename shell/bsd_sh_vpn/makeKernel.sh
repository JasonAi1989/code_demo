#!/bin/sh
#cd /usr/src/sys/i386/compile
#echo "rm SERVER.1u1010 files, please wait a second"
#rm -rf SERVER.1u1010/
#echo "rm finished!"
cd /usr/src/sys/i386/conf/
config SERVER.1u1010
cd ../compile/SERVER.1u1010/
make clean&& make depend && make kernel
cp -f kernel /kernel/GFAkernel
echo "make and copy finished!"

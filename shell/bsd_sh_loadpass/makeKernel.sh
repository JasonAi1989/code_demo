#!/bin/sh


cd /usr/src/sys/amd64/conf/
config SERVER.1600
cd ../compile/SERVER.1600/
make clean

cd /usr/src/kernelapi/generator
./startKernelWrapGen2Coms
./startUserWrapGen2Coms

cd /usr/src/sys/amd64/compile/SERVER.1600/
make depend && make kernel
cp -f /kernel/GFAkernel /kernel/GFAkernel_bak
cp -f kernel /kernel/GFAkernel
cp -f kernel.debug /usr/src/sys/amd64/compile/debug 
echo "make and copy finished!"

#!/bin/sh
cd /usr/src/sys/i386/conf/
config SERVER.1u1010
cd ../compile/SERVER.1u1010/
make kernel
cp kernel /kernel/GFAkernel
echo "make and copy finished!"

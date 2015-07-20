#!/bin/sh

cd /usr/src
make clean

cd ui/generator
make

cd ../../usr.bin
cp systat.src/systat .

cd ../hash
make

cd /usr/src/kernelapi/generator
chmod +x startKernelWrapGen2Coms startUserWrapGen2Coms
./startKernelWrapGen2Coms
./startUserWrapGen2Coms

cd /usr/src
make install-userland
echo "make finished!"

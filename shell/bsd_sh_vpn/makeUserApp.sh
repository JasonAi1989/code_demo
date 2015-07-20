#!/bin/sh
cd /usr/src
make clean && make install-userland
echo "make finished!"

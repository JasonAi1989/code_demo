#!/bin/sh

echo "I'm preload daemod"

export LD_PRELOAD=./preload.so
./mypwd

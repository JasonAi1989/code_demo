#!/bin/sh

echo $1

ret=$(echo $1 | sed 's/#/ /g')

echo "-----"
echo $ret

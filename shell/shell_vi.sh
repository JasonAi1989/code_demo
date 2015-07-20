#!/bin/bash

a=$1
vi $a <<EOF
:%s/file/FILE/g

ZZ
EOF
cat $1
exit 0

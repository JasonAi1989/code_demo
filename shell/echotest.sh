#!/bin/bash

echo -e "1\t2\t3"
echo "$PATH"
echo "$HOME"
echo "$PWD"
echo "$USER"
echo "$UID"
echo "$SHELL"

arg1=10
arg2=23

let result=arg1+arg2
echo "$result"
let result++
echo "$result"

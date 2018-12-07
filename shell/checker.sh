#!/bin/sh
PRODUCT=$1
FILE=$2
echo "product:" $1
echo "file:" $2

if [ "$PRODUCT" = "" ]; then
    echo "please input product"
    exit
fi
LOG=$PRODUCT"_checker.log"
echo "log file:" $LOG
echo "check path:" `pwd`
if [ "$FILE" = "" ]; then
    TAG=`git describe --match *CAA* | awk -v FS=- -v OFS=- '{print $1,$2}'`
    /proj/spr/bin/cc-incremental-check check --target $PRODUCT --branch $TAG | tee $LOG
else
    /proj/spr/bin/cc-incremental-check check --target $PRODUCT --file $FILE | tee $LOG
fi



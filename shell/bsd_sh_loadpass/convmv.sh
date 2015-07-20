#!/bin/sh

##check the arg
if [ ! -n "$1" ] ;then
    echo "you don't have input arg"
    exit
fi

##check the suffix
file=$1
if [ "${file##*.}" = "tgz" ] || [ "${file##*.}" = "gz" ];then
    tar -zxvf $file -C /tmp
else
    echo "Please input *.tgz file"
    exit
fi
 
##check the dir
dir=${file%%.*}
echo $dir|grep -q / && path=${dir%/*} || path=$(pwd) 
dir="/tmp/"${dir##*/}
echo $dir
echo $path
if [ ! -d "$dir" ]; then
    echo "$dir is not a directory"
    exit
fi

stddir="/tmp/ipregionall"
mv $dir $stddir
 
/usr/local/bin/convmv -f UTF-8 -t GBK --notest -r $stddir 
date > $stddir"/ver"

cd $stddir
mv ����[�й�-����] city
mv ����[�й�-ʡ��] provience
mv ����[�й�-��Ӫ��] isp

cd isp
mv ����.txt chinatelecom.txt
mv ��ͨ.txt chinaunicom.txt
mv ��ͨ.txt chinatietong.txt
mv �ƶ�.txt chinamobile.txt
mv �軪.txt gehua.txt
mv ������.txt cernet.txt
mv ���ǿ��.txt greatwall.txt

cd /tmp 
tar -zcvf ipregionall.tar.gz ipregionall 
rm -rf ipregionall 
mv ipregionall.tar.gz $path

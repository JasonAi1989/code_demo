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
mv 掩码[中国-城市] city
mv 掩码[中国-省份] provience
mv 掩码[中国-运营商] isp

cd isp
mv 电信.txt chinatelecom.txt
mv 联通.txt chinaunicom.txt
mv 铁通.txt chinatietong.txt
mv 移动.txt chinamobile.txt
mv 歌华.txt gehua.txt
mv 教育网.txt cernet.txt
mv 长城宽带.txt greatwall.txt

cd /tmp 
tar -zcvf ipregionall.tar.gz ipregionall 
rm -rf ipregionall 
mv ipregionall.tar.gz $path

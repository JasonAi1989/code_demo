#!/bin/bash 
#network #Mike.Xu 
while true
do 
    rx_before=$(ifconfig eth0 |sed -n "8"p|awk '{print $2}'|cut -c 2-)
    tx_before=$(ifconfig eth0 |sed -n "8"p|awk '{print $5}'|cut -c 2-)
    sleep 2 
    rx_after=$(ifconfig eth0|sed -n "8"p|awk '{print $2}'|cut -c 2-) 
    tx_after=$(ifconfig eth0|sed -n "8"p|awk '{print $5}'|cut -c 2-)
    rx_result=$(echo "$rx_after-$rx_before" | bc) 
    tx_result=$(echo "$tx_after-$tx_before" | bc)

    clear
    echo "$(date)"
    echo "down bandwidth: $rx_result (MB/s)"
    echo "up   bandwidth: $tx_result (MB/s)"
    sleep 2 
done

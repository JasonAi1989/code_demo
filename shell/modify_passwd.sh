#!/bin/bash

if [ "$(whoami)" != "root" ]
then
	(sleep 0.1; echo "niksun2K13!"; sleep 0.1; echo "yuanvi2015"; sleep 0.1; echo "yuanvi2015"; sleep 0.1) | passwd
else
	(sleep 0.1; echo "yuanvi2015"; sleep 0.1; echo "yuanvi2015"; sleep 0.1) | passwd
fi

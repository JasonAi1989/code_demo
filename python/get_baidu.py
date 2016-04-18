#!/usr/bin/python

import httplib

def get_baidu():
	conn=httplib.HTTPConnection("www.baidu.com")
	conn.request("GET", "/index.html")
	re = conn.getresponse()
	print re.status, re.reason
	
#####main#####
for i in list(range(0, 1000)):
	get_baidu()

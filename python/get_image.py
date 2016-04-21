#!/usr/local/bin/python3

import urllib.request
import os.path

def get_image_data(addr):
    response=urllib.request.urlopen(addr)
    html=response.read()
    return html

def save_image_to_local(data, path, file_name):
    if os.path.isdir(path) == False:
        print('h')
        os.makedirs(path)

    name=path+'/'+file_name
    f=open(name, 'xb')
    f.write(data)
    f.close()

####main
base_url='http://tu.qzcpic.com/1/'
base_path='animation/'

count=0
for i in range(1, 400):
    for j in range(1, 400):
        url=base_url+str(i)+'/'+str(j)+'.jpg'
        path=base_path+str(i)
        file_name=str(j)+'.jpg'

        data=get_image_data(url)
        save_image_to_local(data, path, file_name)
        
        count = count + 1
        print('count: %d', count)


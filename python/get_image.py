#!/usr/local/bin/python3

import urllib.request
import os.path

def get_image_data(addr):
    try:
        response=urllib.request.urlopen(addr, timeout=30)
        if response.getcode() != 200:
            return None

        html=response.read()

        if len(html) == 0:
            return None
    
        return html
    except socket.timeout as e:
        print('time out')
        return None

def analysis_data(data):
    data_string=str(data)
    find='http://404.safedog.cn'
    p=data_string.find(find)
    if p == -1:
        return 0
    
    return -1

    
def save_image_to_local(data, path, file_name):
    if os.path.isdir(path) == False:
        os.makedirs(path)

    name=path+'/'+file_name
    f=open(name, 'xb')
    f.write(data)
    f.close()

####main
base_url='http://tu.qzcpic.com/1/'
base_path='animation/'

count=0
bad_page=0
max_bad_page=50

for i in range(1, 1000):
    for j in range(1, 1000):
        if bad_page == max_bad_page:
            bad_page = 0
            break
        
        url=base_url+str(i)+'/'+str(j)+'.jpg'
        path=base_path+str(i)
        file_name=str(j)+'.jpg'

        data=get_image_data(url)
        if data == None:
            bad_page += 1
            continue
        
        if analysis_data(data) == -1:
            bad_page += 1
            continue
        
        save_image_to_local(data, path, file_name)
        count += 1

    print('dir ', i, ' count: ', count)


#!/usr/bin/env python3

import os
import re

def findfiles(inputdir):
    files = list()
    for dirpath, dirnames, filenames in os.walk(inputdir):
        #print(dirpath)
        for filename in filenames:
            if re.match(r'.*txt', filename):
                files.append(os.path.join(dirpath, filename))

    return files

files = findfiles('/home/jason')
print(files)

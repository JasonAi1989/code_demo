#!/usr/bin/env python3

import re

if __name__=='__main__':
    text = "aAsmr3idd4bgs7Dlsf9eAF" 
    a = re.split(r'[a-zA-Z]+', text)
    print(a)
    b = re.findall(r'\d', text)
    print(b)
    c=''.join(b)
    print(c)
    d=''.join(a)
    print(d)

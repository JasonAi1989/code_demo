#!/usr/bin/env python3

import re

a = input()
b = re.split(r'\s+', a)
print(a)
print(b)
c = set()
for i in b:
    c.add(int(i))

print(c)

############

d = sorted(set(b))
print(d)

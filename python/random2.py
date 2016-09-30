#!/usr/bin/env python3

import random

def random2(start, stop, m):
    ret = list()
    random.seed()
    for i in range(m):
        ret.append(random.randrange(start, stop))

    return ret

def random3(start, stop, m):
    return random.sample(range(start, stop), m)

if __name__ == '__main__':
    r = random2(1, 100, 10)
    print(r)
    r2 = random3(10,500, 11)
    print(r2)

#!/usr/bin/env python3

def test(num):
    try:
        ret=num/0

    except ZeroDivisionError as e:
        print('erro')


###main

test(10)

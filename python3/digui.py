#! /usr/bin/env python3

import sys

sys.path.append('/home/snow/workspace/github.com/study/python3')
from func import counter as ct


def factorial(n):
    if n == 0 or n == 1:
        return 1
    else:
        return (n * factorial(n-1))




print(factorial(10))
it = ct(20)
print(it())
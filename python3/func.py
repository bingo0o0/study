#! /usr/bin/env python3
# -*- coding:utf-8 -*-

def counter(start_at=0):
    x = start_at
    def incr():
        nonlocal x
        x += 2
        return x
    return incr


if __name__ == '__main__':
    func1 = counter(10)
    func2 = counter(20)
    for x in range(5):
        print(func1())

    print(func2())
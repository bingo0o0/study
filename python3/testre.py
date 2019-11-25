#! /usr/bib/env python3
# -*- coding: utf-8 -*-

import re

pattern = r'''
    ^       # 从头开始匹配
    M{1,3}  # 最少一个M, 最多3个M
    $       # 匹配结尾
'''

ret = re.search(pattern, 'M', re.VERBOSE)
print(ret)

line_number = 0

with open('testre.py', encoding='utf-8') as a_file:
    for a_line in a_file:
        line_number += 1
        print('{:>4}     {}'.format(line_number, a_line.rstrip()))

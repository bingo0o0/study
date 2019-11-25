#! /usr/bin/env python3
# -*- coding:utf-8 -*-

def copy_file(fileName):
    '''拷贝图片文件'''
    with open(fileName, 'rb') as fin, open('out.jpg', 'wb') as fout:
        for line in fin:
            fout.write(line)



if __name__ == '__main__':
    copy_file('test.jpg')
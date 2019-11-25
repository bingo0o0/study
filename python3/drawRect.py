#! /usr/bin/env python3
# coding=utf-8

import cv2 as cv


def draw_rect():
    img = cv.imread("1_anqm_416x736.jpg")

    point_size = 1
    point_color = (0, 0 , 255)
    thickness = 2
    
    cv.rectangle(img, (143,255), (260,365), point_color, thickness)

    cv.namedWindow("image")
    cv.imshow('image', img)
    cv.waitKey (10000) # 显示 10000 ms 即 10s 后消失
    cv.destroyAllWindows()

if __name__ == '__main__':
    draw_rect()
#! /usr/bin/env python3
# -*- codong:utf-8 -*-

person = {'name':'', 'id':0}
team = []

for i in range(3):
    x = person
    x['id'] = i
    team.append(x)


team[0]['name'] = '111'
team[1]['name'] = '222'
team[2]['name'] = '333'


print(team[1])
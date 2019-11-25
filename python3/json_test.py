#! /usr/bin/env python3

import json

data = [{
    'no' : 1,
    'name' : 'Runoob',
    'url' : 'http://www.runoob.com'
}]

json_str = json.dumps(data)
print(data['no'])
print('json原始字符串: ', json_str)
#jj = json_str["name"]
js = json.loads(json_str)
print(type(js))


#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Date    : 2018-11-22 18:05:07
# Author  : Wangjihe (wangjihe.mail@gmail.com)
# Link    : wangjihe.cf

import math

def test_diff_type(v):
	if isinstance(v, str):
		return {'t1':v.replace("a","A"),'t2':v}
	elif isinstance(v, int):
		v+=2
		return v

output=((test_diff_type("123")))
print(output)


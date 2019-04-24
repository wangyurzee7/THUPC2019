#!/bin/python3

s = input().split(" ")
assert(len(s) == 3)
n = int(s[0])
k = int(s[1])
q = int(s[2])
assert(n >= 2)
assert(k >= 1)
assert(n ** k <= 1000000)
assert(q <= 5 * 10 ** 5 and q >= 0)

for i in range(n ** k):
	x = int(input())
	assert(1 <= x and x < 998244353)  # 小于P的正整数

for i in range(q):
	s = input().split(" ")
	assert(len(s) == 2)
	a = int(s[0])
	b = int(s[1])
	assert(0 <= a and a < n ** k)
	assert(0 <= b and b < 998244353)


n = int(input())
assert(0 <= n and n <= 100000)

for i in range(n):
	a = input().split(" ")
	assert(len(a) == 2)
	opt = int(a[0])
	assert(opt == 1 or opt == 2)
	v = int(a[1])
	assert(-2147483648 <= v and v <= 2147483647)

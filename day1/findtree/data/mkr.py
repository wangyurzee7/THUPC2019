from random import *
from sys import *
from os import *

N = int(argv[1])
M = int(argv[2])
W = int(argv[3])
A = argv[4]
print N, M
print "".join([A[randint(0, len(A) - 1)] for i in xrange(W)])
mask = 0
for i in xrange(W):
	mask = mask * 2 + max(randint(0, 3), 1)
if randint(1, 3) != 1:
	mask = 2 ** W - 1
for i in xrange(M):
	print randint(1, N), randint(1, N), eval(argv[5]) & mask
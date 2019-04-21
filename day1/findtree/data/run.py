from random import *
from sys import *
from os import *

N = 70
W = 12
M = [100, 300, 500, 1000, 2000, 5000]
A = ["&", "|", "^", "&&&|^", "&&&&&^^^||", "^^^&|"]
V = ["randint(0,2**W-1)", "randint(0,2**randint(1,W)-1)", "randint(0,2**randint(W/2,W)-1)"]

system("g++ tmp.cpp -o tmp -O2")

Cnt = 0
for m in M:
	for a in A:
		for v in V:
			Cnt += 1
			cmd = "python mkr.py %d %d %d \"%s\" \"%s\" > %d.in" % (N, m, W, a, v, Cnt)
			print cmd
			system(cmd)
			cmd = "/usr/bin/time ./tmp < %d.in > %d.ans" % (Cnt, Cnt)
			print cmd
			system(cmd)
			cmd = "cat %d.ans" % Cnt
			system(cmd)
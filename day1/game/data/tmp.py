from random import randint
from os import system

for i in range(0, 20) : 
	seed = randint(0, int(1e9))
	print("Testcase #%d, working...")
	system("./gen %d > %d.in" % (seed, i + 1))
	system("./std <%d.in >%d.ans" % (i + 1, i + 1))

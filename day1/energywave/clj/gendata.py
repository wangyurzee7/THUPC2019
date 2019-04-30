import os;
import time;
import sys;

NAME = 'spaceship'

def getIn(id):
	return str(id) + '.IN' 

def getOut(id):
	return str(id) + '.ANS' 

def genInput(id, **dictArgs):
	m = dictArgs['m']
	n = dictArgs['n']
	box = dictArgs['box']
	tp = dictArgs['tp']

	nameinput = getIn(id);

	cmd = 'gen %d %d %d %d %s > %s'%(n,box,id,m,tp,nameinput);

	os.system(cmd);

nId = 1

for i in range(0,2):
	genInput(nId,m=4,n=8,box=30,tp='rect')
	nId += 1

for i in range(0,2):
	genInput(nId,m=4,n=8,box=30,tp='usual')
	nId += 1

for i in range(0,2):
	genInput(nId,m=4,n=8,box=40,tp='usual')
	nId += 1

for i in range(0,2):
	genInput(nId,m=4,n=8,box=50,tp='usual')
	nId += 1

for i in range(1,nId):
	nameinput = getIn(i);
	nameoutput = getOut(i);
	cur = time.time()
	os.system('std.exe <%s >%s'%(nameinput,nameoutput));
	print "Test %d completed, Std Time Usage: %0.5fs"%(i,time.time() - cur)

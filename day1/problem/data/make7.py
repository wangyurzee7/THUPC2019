import os
import random

import heapq

id_ = 7

f = open("%d.in"%id_,"w")

n = 100000
print(n,file=f)

for a in range(0,n):
    opt = random.randint(1,2)
    if opt==1:
        v=1
        print(1,v,file=f)
    else:
        v = 1
        print(2,v,file=f)

f.close()

os.system("zhx.exe < %d.in > %d.ans" %(id_,id_))

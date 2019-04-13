import os
import random

import heapq

id_ = 4

f = open("%d.in"%id_,"w")

n = 100000
print(n,file=f)

arr = []
for a in range(0,n):
    opt = random.randint(1,2)
    if len(arr)==0:
        opt=1
    if opt==1:
        v = random.randint(1,100)
        heapq.heappush(arr,v)
        print(1,v,file=f)
    else:
        v = arr[0]
        heapq.heappop(arr)
        print(2,v,file=f)

f.close()

os.system("zhx.exe < %d.in > %d.ans" %(id_,id_))

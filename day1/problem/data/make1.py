import os
import random

id_ = 1

f = open("%d.in"%id_,"w")

n = 6
print(n,file=f)
z = [1,2,3]
random.shuffle(z)
for a in range(0,3):
    print(1,z[a],file=f)
random.shuffle(z)
for a in range(0,3):
    print(2,z[a],file=f)

f.close()

os.system("zhx.exe < %d.in > %d.ans" %(id_,id_))

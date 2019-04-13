import os

for a in range(1,108):
    os.system("zhx.exe < ../data/%d.in > out"%a)
    f=open("out","r")
    v1=int(f.readline()[:-1])
    f=open("../data/%d.ans"%a,"r")
    v2=int(f.readline()[:-1])
    if (v1!=v2):
        print(a)

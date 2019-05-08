import sys
import os

max_n=700
max_m=60000
max_w=100

def err(st):
    sys.stdout.write(st+"\n")
    exit()

if __name__=="__main__":
    n,m=list(map(int,input().split(" ")))
    if not n in range(1,max_n+1):
        err("N out of range")
    if not m in range(1,max_m+1):
        err("M out of range")
    c=list(map(int,input().split(" ")))
    w=list(map(int,input().split(" ")))
    if len(c)!=n or len(w)!=n:
        err("number of C/W does not match N")
    for i in range(n):
        if not c[i] in range(1,n+1):
            err("C_i out of range")
        if not w[i] in range(1,max_w+1):
            err("W_i out of range")
    nxt=[[] for i in range(n)]
    for i in range(m):
        u,v=list(map(int,input().split(" ")))
        if (not u in range(1,n+1)) or (not v in range(1,n+1)):
            err("U/V out of range")
        u-=1
        v-=1
        nxt[u].append(v)
    for i in range(n):
        if c[i]!=1:
            continue
        q,qh,qt=[i],0,0
        vis=[j==i for j in range(n)]
        while qh<=qt:
            u,qh=q[qh],qh+1
            for v in nxt[u]:
                if vis[v]:
                    continue
                if c[v]==1:
                    err("Node {} has a path to Node {} which is invalid.".format(i+1,v+1))
                q.append(v)
                vis[v]=True
                qt+=1
    try:
        buf=input()
    except:
        buf=None
    if buf!=None:
        # print(buf)
        err("Expect eof but something found.")
    sys.stdout.write("OK\n")

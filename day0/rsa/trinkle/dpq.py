import gmpy2
def work(c1,c2,e1,e2,n):
    gcd,s,t=gmpy2.gcdext(e1,e2)
    if s<0:
        s=-s
        c1=gmpy2.invert(c1,n)
    if t<0:
        t=-t
        c2=gmpy2.invert(c2,n)
    return gmpy2.powmod(c1,s,n)*gmpy2.powmod(c2,t,n)%n
T=int(input())
for __ in range(T):
        s=raw_input().split(' ')
        print(work(int(s[0]),int(s[1]),int(s[2]),int(s[3]),int(s[4])))

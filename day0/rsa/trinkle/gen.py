import numpy as np
def power(t,k,p):
# return t^k%p
	f=1
	while k>0:
		if k%2==1:
			f=f*t%p
		k/=2
		t=t*t%p
	return f
def gcd(x,y):
	if y==0:
		return x
	else:
		return gcd(y,x%y)
def exgcd(a,b):
	if b==0:
		return (a,1,0)
	else:
		(g,y,x)=exgcd(b,a%b)
		return (g,x,y-x*(a//b))
def inv(a,p):
# return a^{-1}%p
	(g,x,y)=exgcd(a,p)
	return (x%p+p)%p

name='prime.txt'
a=open(name).read().split('\n')[:-1]
bigp=[]
for i in a:
	bigp.append(int(i))
num=len(bigp)
###### gen prime
top=1000000
table=[0]*(top+10)
table[0]=table[1]=1
i=2
while i<=top:
	if table[i]==0:
		j=i+i
		while j<=top:
			table[j]=1
			j+=i
	i+=1
prime=[]
for i in range(2,top+1):
	if(table[i]==0):
		prime.append(i)
# print(prime)
######
pre='1'
with open(pre+'.in','w') as fi:
	with open(pre+'.ans','w') as fo:
		T=10000
		fi.write('%d\n'%T)
		for __ in range(T):
			p=bigp[np.random.randint(num)]
			q=bigp[np.random.randint(num)]
			n=p*q
			r=(p-1)*(q-1)
			while True:
				e=prime[np.random.randint(len(prime))]
				if gcd(r,e)==1 and e<r:
					break
			e1=e
			while True:
				e=prime[np.random.randint(len(prime))]
				if gcd(r,e)==1 and gcd(e,e1)==1 and e<r:
					break
			e2=e
			while True:
				m=int(np.random.rand()*n)
				# m=19260817
				if(gcd(n,m)==1):
					break
			fo.write('%d\n'%m)
			c1=power(m,e1,n)
			c2=power(m,e2,n)
			fi.write('%d %d %d %d %d\n'%(c1,c2,e1,e2,n))

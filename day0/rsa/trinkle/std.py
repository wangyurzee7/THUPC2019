def power(t,k,p):
# return t^k%p
	f=1
	while k>0:
		if k%2==1:
			f=f*t%p
		k/=2
		t=t*t%p
	return f
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

T=int(input())
for __ in range(T):
	s=raw_input().split(' ')
	c1,c2,e1,e2,n=int(s[0]),int(s[1]),int(s[2]),int(s[3]),int(s[4])
	# if c1>2**1024 or c2>2**1024 or e1>2**1024 or e2>2**1024 or n>2**1024:
		# print("error! %d"%__)
	(gcd,s,t)=exgcd(e1,e2)
	if s<0:
		s=-s
		c1=inv(c1,n)
	elif t<0:
		t=-t
		c2=inv(c2,n)
	m=(power(c1,s,n)*power(c2,t,n))%n
	print(m)
#include<bits/stdc++.h>
using namespace std;
#define P 998244353 
#define ll long long
int n,m,N,i,j,k,a[75][75][4096],b[4096],g[75][75];
char c[100];
int Pow(int x,int y)
{
	int s=1;
	for(;y;y>>=1,x=(ll)x*x%P)if(y&1)s=(ll)s*x%P;
	return s;
}
void DFT(int *a)
{
	int i,j,k,l;
	for(l=0;l<N;l++)for(i=1<<l,j=0;j<1<<N;j++)if(j&i)
	{
		if(c[l]=='&')a[j^i]=(a[j^i]+a[j])%P;
		else if(c[l]=='|')a[j]=(a[j^i]+a[j])%P;
		else
		{
			k=(a[j^i]+a[j])%P;
			a[j]=(a[j^i]+P-a[j])%P;
			a[j^i]=k;
		}
	}
}
void IDFT(int *a)
{
	int i,j,k,l;
	for(l=0;l<N;l++)for(i=1<<l,j=0;j<1<<N;j++)if(j&i)
	{
		if(c[l]=='&')a[j^i]=(a[j^i]+P-a[j])%P;
		else if(c[l]=='|')a[j]=(P-a[j^i]+a[j])%P;
		else
		{
			k=(ll)(a[j^i]+a[j])*(P+1)/2%P;
			a[j]=(ll)(a[j^i]+P-a[j])*(P+1)/2%P;
			a[j^i]=k;
		}
	}
}
int work()
{
	int ans=1,i,j,k,l;
	for(i=1;i<n;i++)
	{
		for(j=i;j<n;j++)if(g[j][i])break;
		if(j==n)return 0;
		if(j!=i)
		{
			ans=P-ans;
			for(k=i;k<n;k++)swap(g[i][k],g[j][k]);
		}
		ans=(ll)ans*g[i][i]%P;
		for(j=i+1,l=P-Pow(g[i][i],P-2);j<n;j++)for(k=n-1;k>=i;k--)g[j][k]=(g[j][k]+(ll)g[i][k]*g[j][i]%P*l)%P;
	}
	return ans;
}
int main()
{
	freopen("findtree.in","r",stdin);
	freopen("findtree.out","w",stdout);
	scanf("%d%d%s",&n,&m,c);
	N=strlen(c);
	while(m--)
	{
		scanf("%d%d%d",&i,&j,&k);
		a[i][j][k]=(a[i][j][k]+P-1)%P;
		a[i][i][k]++;
		a[j][j][k]++;
		a[j][i][k]=(a[j][i][k]+P-1)%P;
	}
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)DFT(a[i][j]);
	for(i=0;i<1<<N;i++)
	{
		for(j=1;j<n;j++)for(k=1;k<n;k++)g[j][k]=(P+a[j][k][i])%P;
		b[i]=work();
	}
	IDFT(b);
	for(i=(1<<N)-1;~i;i--)if(b[i])break;
	cout<<i<<endl;
	return 0;
}


#include <bits/stdc++.h>

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return ret;
}

const int N(5005);
const int inf(0x7fffffff);
inline int median(int* a,int na,int* b,int nb){
	if (na<nb) swap(na,nb),swap(a,b);
	int k=(na+nb+1)>>1;
	int l=max(k-nb-1,0),r=k,mid;
	a[0]=b[0]=0;
	a[na+1]=b[nb+1]=inf;
	while (l+1<r){
		mid=(l+r)>>1;
		(a[mid]<=b[k-mid]?l:r)=mid;
	}
	return min(a[l+1],b[k-l]);
}

int m;
int a[N][N];
int n[N];
unsigned int g[N],h[N];

int main(){
	m=read();
	for (int i=1;i<=m;++i){
		n[i]=read();
		for (int j=1;j<=n[i];++j)
			a[i][j]=read();
		sort(a[i]+1,a[i]+n[i]+1);
	}
	memset(g,0,sizeof(g));
	memset(h,0,sizeof(h));
	for (int i=1;i<=m;++i)for (int j=i;j<=m;++j){
		unsigned int tmp=median(a[i],n[i],a[j],n[j]);
		// printf("%u %u %u   %u\n",i,j,tmp,tmp+i+j);
		h[i]^=(tmp+i+j);
		if (i!=j){
			h[j]^=(tmp+i+j);
		}
	}
	puts("");
	for (int i=1;i<=m;++i) printf("%u\n",h[i]);
	return 0;
}

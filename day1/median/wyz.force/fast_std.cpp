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

const int N(3005);
const int inf(1e9);

int n;
inline int median(int* a,int* b){
	int l=0,r=n+1,mid;
	a[0]=b[0]=0;
	a[n+1]=b[n+1]=inf+1;
	while (l+1<r){
		mid=(l+r)>>1;
		(a[mid]<=b[n-mid+1]?l:r)=mid;
	}
	return max(a[l],b[n-l]);
}

int m;
int a[N][N];

int main(){
	m=read();
	n=read();
	for (int i=1;i<=m;++i)
		for (int j=1;j<=n;++j)
			a[i][j]=read();
	for (int i=1;i<=m;++i)for (int j=i+1;j<=m;++j){
		printf("%d\n",median(a[i],a[j]));
	}
	return 0;
}

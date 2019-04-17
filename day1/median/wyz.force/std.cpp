#include <bits/stdc++.h>

using namespace std;
const int N(5005);
const int inf(1e9);

int n;
inline int median(int* a,int* b){
	int l=0,r=n+1;
	a[0]=b[0]=0;
	a[n+1]=b[n+1]=inf+1;
	while (l+1<r){
		int mid=(l+r)>>1;
		if (a[mid]<=b[n-mid+1]&&b[n-mid]<=a[mid+1])
			l=mid;
		else if (b[n-mid]>a[mid+1])
			l=mid;
		else
			r=mid;
	}
	return max(a[l],b[n-l]);
}

int m;
int a[N][N];

int main(){
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;++i)
		for (int j=1;j<=n;++j)
			scanf("%d",&a[i][j]);
	for (int i=1;i<=m;++i)for (int j=i+1;j<=m;++j){
		printf("%d\n",median(a[i],a[j]));
	}
	return 0;
}

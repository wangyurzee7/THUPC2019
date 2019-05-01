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

typedef long long ll;
const int N=305;
const int P=int(1e9)+7;
const int MAX_M=505;
// int __cnt=0;
int add(int x,int y){
    // ++__cnt;
    int tmp=x+y;
    if (tmp>=P) return tmp-P;
    else return tmp;
}

int n,c;
int C[2],D[2];
int bl[N],s[N],ban[N];
int citySize[N];

int ans;
int color[N],clique[N];
int sumC[2],sumD[2];

void dfs_school(int now){
    if (now>n){
        ++ans;
        return;
    }
    for (int i=0;i<2;++i){
        clique[now]=i;
        sumD[i]+=s[now];
        if (sumD[i]<=D[i]&&ban[now]!=((color[bl[now]]<<1)^i))
            dfs_school(now+1);
        sumD[i]-=s[now];
    }
}

void dfs_city(int now){
    while (now<=c&&!citySize[now]) ++now;
    if (now>c){
        dfs_school(1);
        return;
    }
    for (int i=0;i<2;++i){
        color[now]=i;
        sumC[i]+=citySize[now];
        if (sumC[i]<=C[i])
            dfs_city(now+1);
        sumC[i]-=citySize[now];
    }
}

void work(){
    n=read();c=read();
    for (int i=0;i<2;++i) C[i]=read();
    for (int i=0;i<2;++i) D[i]=read();
    memset(citySize,0,sizeof(citySize));
    for (int i=1;i<=n;++i){
        bl[i]=read();
        s[i]=read();
        citySize[bl[i]]+=s[i];
    }
    memset(ban,-1,sizeof(ban));
    for (int k=read();k;--k){
        int id=read();
        ban[id]=read();
    }
    
    ans=0;
    dfs_city(1);
    sumC[0]=sumC[1]=0;
    sumD[0]=sumD[1]=0;
    printf("%d\n",ans);
}


int main(){
#ifndef __TUACK__
    freopen("mentor.in","r",stdin);
    freopen("mentor.out","w",stdout);
#endif
	for (int T=read();T;T--)
        work();
	return 0;
}


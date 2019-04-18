#include <bits/stdc++.h>

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10+(ch-48);
		ch=getchar();
	}
	return ret;
}

const int M=5005;
const int N=505;
const int W=15;
const int B=1<<W;
const int b=B-1;


int m;
int a[M][N];
int n[M];
int sumN;
void input(){
    m=read();
    sumN=0;
    for (int i=0;i<m;++i){
        n[i]=read();
        sumN+=n[i];
        for (int j=n[i]-1;~j;--j)
            a[i][j]=read();
    }
}
pair<int,int> sorted[N*M],_tmp[N*M];
int sum[B];
void sorting(){
    memset(sum,0,sizeof(sum));
    for (int i=0;i<m;++i) for (int j=n[i]-1;~j;--j)
        ++sum[a[i][j]&b];
    for (int i=1;i<B;++i)
        sum[i]+=sum[i-1];
    for (int i=0;i<m;++i) for (int j=n[i]-1;~j;--j)
        _tmp[--sum[a[i][j]&b]]=make_pair(a[i][j],i);
    
    memset(sum,0,sizeof(sum));
    for (int i=0;i<sumN;++i)
        ++sum[_tmp[i].first>>m];
    for (int i=1;i<B;++i)
        sum[i]+=sum[i-1];
    for (int i=sumN-1;~i;--i)
        sorted[--sum[_tmp[i].first>>m]]=make_pair(_tmp[i].first,_tmp[i].second);
}
int ans[M];
int cur[M],pre[M],nxt[M];
void solve(){
    memset(ans,0,sizeof(ans));
    int* tmp_ptr=new int[N<<1];
    memset(tmp_ptr,-1,sizeof(int)*(N<<1));
    int* head=tmp_ptr+N;
    for (int i=0;i<m;++i){
        cur[i]=-n[i];
        pre[i]=-1;nxt[i]=head[cur[i]];pre[head[cur[i]]]=i;
        head[cur[i]]=i;
    }
    for (int k=0;k<sumN;++k){
        assert(k==0||sorted[k].first>=sorted[k-1].first);
        int val=sorted[k].first,i=sorted[k].second;
        if (pre[i]!=-1) nxt[pre[i]]=nxt[i];
        else head[cur[i]]=nxt[i];
        if (nxt[i]!=-1) pre[nxt[i]]=pre[i];
        
        cur[i]+=2;
        // printf("[val=%d  i=%d  cur[i]=%d]\n",val,i,cur[i]);
        if (cur[i]==0||cur[i]==1) ans[i]^=(val+i+i+2);
        for (int j=head[-cur[i]],tmp;j!=-1;j=nxt[j]){
            // printf("j=%d   cur[j]=%d\n",j,cur[j]);
            tmp=(val+i+j+2);
            ans[i]^=tmp;
            ans[j]^=tmp;
        }
        for (int j=head[1-cur[i]],tmp;j!=-1;j=nxt[j]){
            // printf("j=%d   cur[j]=%d\n",j,cur[j]);
            tmp=(val+i+j+2);
            ans[i]^=tmp;
            ans[j]^=tmp;
        }
        
        pre[i]=-1;nxt[i]=head[cur[i]];pre[head[cur[i]]]=i;
        head[cur[i]]=i;
    }
    
    delete[] tmp_ptr;
}
void output(){
    for (int i=0;i<m;++i)
        printf("%d\n",ans[i]);
}

int main(){
    input();
    sorting();
    solve();
    output();
	return 0;
}

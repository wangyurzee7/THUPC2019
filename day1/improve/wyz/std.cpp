#include <bits/stdc++.h>

using namespace std;

const int N=705;
namespace Improve{
class Improve{
private:
    int n;
    int col[N],w[N];
    bitset<N> d[N];
    void input(){
        int m;
        auto _scan=scanf("%d%d",&n,&m);
        for (int i=0;i<n;++i) _scan=scanf("%d",&col[i]);
        for (int i=0;i<n;++i) _scan=scanf("%d",&w[i]);
        memset(d,0,sizeof(d));
        for (int i=0;i<n;++i) d[i][i]=1;
        for (int i=0;i<m;++i){
            int u,v;
            _scan=scanf("%d%d",&u,&v);
            d[u-1][v-1]=1;
        }
    }
    int ans;
    int sum[N];
    void solve(){
        ans=0;
        for (int i=0;i<n;++i) if (col[i]==1){
            memset(sum,0,sizeof(sum));
            for (int j=0;j<n;++j) if (i!=j&&d[i][j]){
                assert(col[j]!=1);
                sum[col[j]]+=w[j];
            }
            int mx=0;
            for (int j=0;j<n;++j)
                mx=max(mx,sum[j]);
            ans=max(ans,mx/w[i]);
        }
    }
    void output(){
        printf("%d\n",ans);
    }
public:
    void main(){
        input();
        solve();
        output();
    }
};
}

int main(){
    Improve::Improve().main();
	return 0;
}

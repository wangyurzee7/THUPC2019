#include <bits/stdc++.h>

using namespace std;

namespace mentor{
    typedef long long ll;
    const int P=998244353;
    const int N=1005;
    const int MAX_M=2505;
    void inc(int &x,int y){if ((x+=y)>=P) x-=P;}
    void inc(int &x,ll y){x=(x+y)%P;}
    class Mentor{
    private:
        class DpNode{
        private:
            bool active;
            bool transed; // Does array `pre` should be recalculated?
            vector<int> f,pre;
            int m[2];
            int nows;
        public:
            void print(){
                for (int i=max(0,nows-m[1]);i<=nows&&i<=m[0];++i){
                    printf("f[%d]=%d ;  ",i,f[i]);
                }
                puts("");
            }
            void init(int* _m,bool initialMask=true){
                memcpy(m,_m,sizeof(m));
                f.resize(m[0]+1,0);
                if (initialMask){
                    active=true;
                    f[0]=1;
                }
                else active=false;
                pre.resize(m[0]+1,0);
                nows=0;
                transed=true;
            }
            DpNode& operator +=(const DpNode& other){
                if (!other.active)
                    return *this;
                if (!active){
                    *this=other;
                    return *this;
                }
                assert(nows==other.nows);
                for (int i=max(0,nows-m[1]);i<=nows&&i<=m[0];++i)
                    inc(f[i],other.f[i]);
                return *this;
            }
            DpNode operator +(const DpNode& other){
                DpNode ret=*this;
                ret+=other;
                return ret;
            }
            void trans(int w,int ban=-1){
                if (!active) return;
                // printf("m[0]=%d m[1]=%d w=%d ban=%d\n",m[0],m[1],w,ban);
                nows+=w;
                if (nows>m[0]+m[1]&&nows-w<=m[0]-m[1])
                    for (int i=0;i<=m[0];++i) f[i]=0;
                if (nows>m[0]+m[1]) return;
                for (int i=min(nows,m[0]);i>=0;--i){
                    if (i<nows-m[1]){
                        f[i]=0;
                        continue;
                    }
                    if (ban==1) f[i]=0;
                    if (i>=w&&ban!=0) inc(f[i],f[i-w]);
                }
            }
            int sum(int l,int r){
                if (!active||l>r) return 0;
                if (transed){
                    pre[0]=f[0];
                    for (int i=1;i<=m[0];++i){
                        pre[i]=pre[i-1];
                        inc(pre[i],f[i]);
                    }
                    transed=false;
                }
                l=max(l,max(0,nows-m[1]));
                r=min(r,min(nows,m[0]));
                int ret=l>0?pre[r]-pre[l-1]:pre[r];
                if (ret<0) ret+=P;
                return ret;
            }
            int operator [](const int& i){
                return f[i];
            }
        };
    private:
        int c,n,m[3][2],sumS;
        int bl[N],s[N],pf[N];
        bool isSp[N];
        vector<int> city2sch[N];
        int citySize[N];
        DpNode f,g; // f->dp_city; g->dp_school
        DpNode dp[MAX_M],tmp[2][MAX_M];
        int color(int i){return pf[i]>>1;}
        int clique(int i){return pf[i]&1;}
        void input(){
            scanf("%d%d",&n,&c);
            for (int i=0;i<2;++i)
                for (int j=0;j<2;++j)
                    scanf("%d",&m[i][j]);
            sumS=0;
            for (int city=1;city<=c;++city) city2sch[city].clear();
            memset(citySize,0,sizeof(citySize));
            int sumSp=0;
            for (int i=1;i<=n;++i){
                scanf("%d%d",&bl[i],&s[i]);
                sumS+=s[i];
                city2sch[bl[i]].push_back(i);
                citySize[bl[i]]+=s[i];
                sumSp+=s[i];
            }
            for (int k=0;k<2;++k) m[2][k]=min(m[1][k],sumSp);
            memset(pf,-1,sizeof(pf));
            memset(isSp,0,sizeof(isSp));
            int k;scanf("%d",&k);
            while (k--){
                int i;scanf("%d",&i);
                scanf("%d",&pf[i]);
                isSp[bl[i]]=true;
            }
        }
        int nowM[3];
        #define rep(_i,_t) for(int _i=max(0,nowM[_t]-m[_t][1]);_i<=m[_t][0]&&_i<=nowM[_t];++_i)
        void solve(){
            f.init(m[0]);
            g.init(m[1]);
            for (int i=0;i<=m[0][0];++i)
                dp[i].init(m[2],i==0); // O(m^2)
            for (int sch=1;sch<=n;++sch) if (pf[sch]==-1) g.trans(s[sch]); // O(nm)
            for (int k=0;k<3;++k) nowM[k]=0;
            for (int city=1;city<=c;++city) if (isSp[city]){
                nowM[0]+=citySize[city];
                int _cs=citySize[city];
                for (int t=0;t<2;++t) rep(i,0){ // O(k^2ms)
                    int j=i-(t^1)*_cs;
                    if (j<0||j>m[0][0]){
                        tmp[t][i].init(m[2],false);
                        continue;
                    }
                    tmp[t][i]=dp[j];
                }
                // puts("transing dp");
                for (int sch:city2sch[city]) if (pf[sch]!=-1){
                    nowM[2]+=s[sch];
                    for (int t=0;t<2;++t) rep(i,0) // O(k^2ms)
                        tmp[t][i].trans(s[sch],color(sch)==t?clique(sch):-1);
                }
                rep(i,0)
                    dp[i]=tmp[0][i]+tmp[1][i];
            }
            else if (citySize[city])
                f.trans(citySize[city]); // O(nm)
            // puts("solved");
        }
        void output(){
            int ans=0;
            rep(i,0)rep(j,2)
                inc(ans,1LL*f.sum(sumS-i-m[0][1],m[0][0]-i)*g.sum(sumS-j-m[1][1],m[1][0]-j)%P*dp[i][j]);
            printf("%d\n",ans);
        }
    public:
        void main(){
            input();
            solve();
            output();
            // f.print();
            // g.print();
            // for (int i=0;i<=3;++i) dp[i].print();
        }
    };
}
int main(){
#ifndef __TUACK__
    freopen("mentor.in","r",stdin);
    freopen("mentor.out","w",stdout);
#endif
    int T;
    scanf("%d",&T);
    while (T--) mentor::Mentor().main();
    return 0;
}

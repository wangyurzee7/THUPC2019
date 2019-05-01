#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define percent(x) (Random::sharedInstance()->rand()%100<x)


using namespace std;

class Random{ // Singleton
private:
    Random(){}
    Random(const Random&){}
    Random& operator =(const Random&){}
    static Random* instance;
public:
    static Random* sharedInstance(){
        if (instance==nullptr)
            instance=new Random();
        return instance;
    }
private:
    unsigned int seed;
public:
    void srand(unsigned int _seed){
        seed=_seed;
    }
    unsigned int randU(){
        seed^=(seed<<17)^(seed>>7);
        seed+=19260817;
        seed^=(seed<<17)^(seed>>7);
        return seed;
    }
    unsigned long long randULL(){
        unsigned long long ret=randU();
        ret=(ret<<32)^randU();
        return ret;
    }
    int rand(){
        int ret=randU()>>2;
        return ret;
    }
    const int base=2;
    int rand_log(int ub){
        return pow(base,1.0*rand()/(1<<30)*(log(ub)/log(base)));
    }
    template<typename T> void random_shuffle(T* st,T* ed){
        for (int i=ed-st;i;--i)
            swap(st[i-1],st[rand()%i]);
    }
};
Random* Random::instance=nullptr;
Random* rnd=Random::sharedInstance();

void unqPick(int *a,int l,int r){
    for (int i=l;i<=r;++i) a[i-l]=i;
    for (int k=0;k<7;++k) Random::sharedInstance()->random_shuffle(a,a+(r-l+1));
}
void unqPick(int *a,int n){
    unqPick(a,1,n);
}
bool inRange(int x,int l,int r){return l<=x&&x<=r;}
void fineTune(int &a){
    if (a>0) a-=Random::sharedInstance()->rand()%2*Random::sharedInstance()->rand()%int(sqrt(a));
}

#define mp make_pair
#define pb push_back
#define fi first
#define se second

const int MAX_N=1005;
const int MAX_K=55;
const int maxs=10;
class MentorData{
public:
    int n,c;
    int m[2][2];
    int b[MAX_N],s[MAX_N];
    int k;
    int id[MAX_N],p[MAX_K];
private:
    void ast(){
        assert(0<n);
        assert(0<c&&c<=n);
        int M=0;
        for (int i=0;i<4;++i){
            assert(0<m[i>>1][i&1]);
            M=max(M,m[i>>1][i&1]);
        }
        for (int i=1;i<=n;++i){
            assert(0<b[i]&&b[i]<=c);
            assert(0<s[i]&&s[i]<=M&&s[i]<=maxs);
        }
        assert(0<=k);
        for (int i=1;i<=k;++i){
            assert(1<=id[i]&&id[i]<=n);
            for (int j=1;j<i;++j)
                assert(id[i]!=id[j]);
            assert(0<=p[i]&&p[i]<4);
        }
    }
    int _a[MAX_N],_b[MAX_N];
public:
    void print(){
        ast();
        if (rnd->rand()&1) swap(m[1][0],m[1][1]);
        printf("%d %d\n",n,c);
        for (int i=0;i<4;++i){
            printf("%d",m[i>>1][i&1]);
            if (i==3) puts("");
            else putchar(' ');
        }
        for (int i=1;i<=n;++i) _a[i]=_b[i]=i;
        rnd->random_shuffle(_a+1,_a+c+1);
        rnd->random_shuffle(_b+1,_b+n+1);
        for (int i=1;i<=n;++i)
            printf("%d %d\n",_a[b[_b[i]]],s[_b[i]]);
        printf("%d\n",k);
        for (int i=1;i<=n;++i) _a[i]=i;
        rnd->random_shuffle(_a+1,_a+k+1);
        for (int i=1;i<=k;++i)
            printf("%d %d\n",_a[id[_a[i]]],p[_a[i]]);
    }
};

MentorData gen(int N,int C,int K,int M,int type){
    if (K==N){
        if (percent(50)) K/=2;
        fineTune(K);
        if (N==1&&type!=2) K=1;
    }
    MentorData ret;
    int n=ret.n=N;
    int k=ret.k=K;
    int c=ret.c=C;
    int s[2]={0,0};
    for (int i=0;i<4;++i){
        int now=M;
        if (type==3&&i==3) now=sqrt(now);
        fineTune(now);
        s[i>>1]+=now;
        ret.m[i>>1][i&1]=now;
    }
    M=0;
    for (int i=0;i<4;++i){
        M=max(M,ret.m[i>>1][i&1]);
    }
    int sum=min(s[0],s[1]);
    if (type==1) sum=0.75*sum;
    else if (type!=5) sum=0.9*sum;
    for (int i=1;i<=n;++i){
        if (type==5)
            ret.b[i]=i%c+1;
        else if (type==4)
            ret.b[i]=i%min(c,max(1,k))+1;
        else if (type==3&&i>1&&percent(50))
            ret.b[i]=ret.b[rnd->rand()%(i-1)+1];
        else ret.b[i]=rnd->rand()%c+1;
        ret.s[i]=1;
        sum-=ret.s[i];
    }
    bool exist[MAX_N];
    memset(exist,0,sizeof(exist));
    for (int i=1;i<=k;++i){
        do ret.id[i]=rnd->rand()%n+1;
        while (exist[ret.id[i]]);
        if (type==4) ret.id[i]=i;
        exist[ret.id[i]]=true;
        if (type==2||type==3){
            sum+=ret.s[ret.id[i]];
            ret.s[ret.id[i]]=min(M,maxs);
            sum-=ret.s[ret.id[i]];
        }
        
        ret.p[i]=rnd->rand()%4;
    }
    assert(sum>=0);
    for (;sum>0;--sum){
        int x,_i=0;
        do x=rnd->rand()%n+1;
        while (ret.s[x]==min(M,maxs)&&(++_i<10));
        if (_i>=10) break;
        ++ret.s[x];
    }
    
    return ret;
}

int main(int argc,char **argv){
    unsigned int seed=argc>1?atoi(argv[1]):time(0);
    int N=argc>2?atoi(argv[2]):500;
    int C=argc>3?atoi(argv[3]):N;
    int K=argc>4?atoi(argv[4]):min(N,30);
    int M=argc>5?atoi(argv[5]):2500;
    int T=argc>6?atoi(argv[6]):5;
    rnd->srand(seed);
    
    printf("%d\n",T);
    for (int t=1;t<=T;++t)
        gen(N,C,K,M,t).print();
    
    return 0;
}

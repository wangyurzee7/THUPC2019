#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define percent(x) (rand()%100<x)


using namespace std;
void EXIT(string st){
	cerr<<st<<endl;
	exit(0);
}

void unqPick(int *a,int l,int r){
	for (int i=l;i<=r;++i) a[i-l]=i;
	for (int k=0;k<7;++k) random_shuffle(a,a+(r-l+1));
}
void unqPick(int *a,int n){
	unqPick(a,1,n);
}
ull randULL(){return ((ull)rand()<<30)^((ull)rand()<<50)^rand();}
ll Rand(ll mod){return (unsigned long long)rand()*rand()*rand()*rand()%mod;}
const int base=2;
int Rand_log(int ub){return pow(base,1.0*rand()/RAND_MAX*(log(ub)/log(base)));}



const int M(10005);
const int N(1005);
int a[M][N];
const int inf=int(1e9)+1;
int b[M];
int flag;

void gen(int m,int n,int type){
	if (type==0){
		for (int i=1;i<=m;++i)
			for (int j=1;j<=n;++j)
				a[i][j]=randULL()%inf;
	}
	else if (type==1){
		for (int i=1;i<=m;++i)
			for (int j=1;j<=n;++j)
				a[i][j]=rand()%2;
	}
	else if (type==2){
		for (int i=1;i<=n;++i) b[i]=randULL()%inf+1;
		sort(b+1,b+n+1);
		for (int i=1;i<=m;++i){
			int top=randULL()%(inf-1)+1;
			for (int j=1;j<=n;++j){
				int tmp1=sqrt(((long double)rand()/RAND_MAX)*top*top);
				int tmp2=sqrt(((long double)rand()/RAND_MAX)*(inf-top)*(inf-top));
				int x;
				if (percent(50)) x=top-tmp1;
				else x=top+1+tmp2;
				if (percent(50)) x=b[1LL*(x-1)*n/inf+1];
				if (1<=x&&x<=inf);
				else{
					cerr<<top<<' '<<tmp1<<' '<<tmp2<<' '<<x<<endl;
					EXIT("faq");
				}
				a[i][j]=x;
			}
		}
	}
	else if (type==3){
		for (int i=1;i<=m;++i)
			for (int j=1;j<=n;++j)
				a[i][j]=inf-rand()%n;
	}
	
	printf("%d\n",m);
	for (int i=1;i<=m;++i){
		int n0=n-rand()%flag;
		printf("%d",n0);
		for (int j=1;j<=n0;++j){
			printf(" %d",a[i][j]);
		}
		puts("");
	}
}

int main(int argc,char **argv){
	unsigned int seed=argc>1?atoi(argv[1]):time(0);
	int type=argc>2?atoi(argv[2]):0;
	flag=argc>3?atoi(argv[3]):2;
	int m=argc>4?atoi(argv[4]):10000;
	int n=argc>5?atoi(argv[5]):500;
	
	srand(seed);
	gen(m,n,type);
	return 0;
}

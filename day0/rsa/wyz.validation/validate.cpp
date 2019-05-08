#include <bits/stdc++.h>
#include "testlib.h"
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

void readEOLN(){
	char ch=inf.readChar();
	if (ch=='\n') return;
	ensuref(ch=='\r',"Expected EOLN!!!");
	inf.readEoln();
}

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

int main(int argc,char** argv){
	registerValidation();

	const int maxT(10000);
	const ll minN((1LL<<8)+1);
	const ll maxN((1ULL<<63)-1);
	
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testdata \"%s\"...",argv[1]);
	}
	
	int T=inf.readInt(1,maxT,"T");
	readEOLN();

	for (int i=1;i<=T;++i){
		inf.readLong(1,maxN,format("c1[%d]",i));inf.readSpace();
		inf.readLong(1,maxN,format("c2[%d]",i));inf.readSpace();
		ll e1=inf.readLong(1,maxN,format("e1[%d]",i));inf.readSpace();
		ll e2=inf.readLong(1,maxN,format("e2[%d]",i));inf.readSpace();
		ll N=inf.readLong(minN,maxN,format("N[%d]",i));
		readEOLN();
		ensuref(gcd(e1,e2)==1,"Testcase#%d : gcd(e1,e2) not equals to 1.",i);
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}

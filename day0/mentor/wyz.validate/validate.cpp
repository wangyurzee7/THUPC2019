#include <bits/stdc++.h>
#include "testlib.h"
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;
const int maxCas=10;
const int ranges[maxCas+1][4]={
    {1000,1000,30,2500},
    {1,1,1,1},
    {10,10,10,100},
    {20,20,0,100},
    {30,30,0,100},
    {30,30,30,500},
    {500,500,0,1000},
    {500,30,30,1000},
    {500,500,30,1000},
    {1000,1000,0,2500},
    {1000,1000,30,2500},
};
const int maxs=10;
const int TRange=5;
inline int nRange(int id){return ranges[id][0];}
inline int cRange(int id){return ranges[id][1];}
inline int kRange(int id){return ranges[id][2];}
inline int MRange(int id){return ranges[id][3];}
int cas,samples;


#define N //to be filled!!!!!!!!!!!!!!!!!!!!!
int n;
void check(char* fname,int index){
	printf("Validating data #%d ( file %s ) ...  ",index,fname);
	freopen(fname,"r",stdin);
	registerValidation();
/*
	testlib using notes:
	inf.readInt(l,r,"Variable name");
	inf.readSpace();
	inf.readEoln();
	format("%d",num);
	ensuref(condition,"Info %d",num);
*/
int T=inf.readInt(0,TRange);
inf.readEoln();
for (int t=1;t<=T;++t){
    int n,c;
    n=inf.readInt(index==0?1:nRange(index),nRange(index));
    inf.readSpace();
    c=inf.readInt(index==0?1:cRange(index),max(n,cRange(index)));
    inf.readEoln();
    int m[2][2],M=0;
    for (int i=0;i<4;++i){
        int now=inf.readInt(1,MRange(index));
        if (i==3)
            inf.readEoln();
        else
            inf.readSpace();
        M=max(M,now);
        m[i>>1][i&1]=now;
    }
    for (int i=1;i<=n;++i){
        int b,s;
        b=inf.readInt(1,c);
        inf.readSpace();
        s=inf.readInt(1,min(maxs,M));
        inf.readEoln();
    }
    int k=inf.readInt(nRange(index)<=30||index==0?0:kRange(index),kRange(index));
    inf.readEoln();
    bool* exist=new bool[n+1];
    for (int i=1;i<=n;++i) exist[i]=false;
    for (int i=1;i<=k;++i){
        int x=inf.readInt(1,n);
        ensuref(!exist[x],"i[%d] of limit already exists.",i);
        exist[x]=true;
        inf.readSpace();
        int p=inf.readInt(0,3);
        inf.readEoln();
    }
    delete[] exist;
}
	
	inf.readEof();
	fclose(stdin);
	puts("OK~");
}

int main(int argc,char** argv){
	registerGen(argc, argv, 1);
	if (argc>1){
		check(argv[1],argc>2?atoi(argv[2]):0);
		return 0;
	}
    cas=10;
	for (int i=1;i<=cas;++i){
		char fname[233];
		sprintf(fname,"../data/%d.in",i);
		check(fname,i);
	}
	puts("All finaltests are checked.");
    samples=2;
	for (int i=1;i<=samples;++i){
		char fname[233];
		sprintf(fname,"../down/%d.in",i);
		check(fname,0);
	}
	puts("All pretest are checked.");
	
	return 0;
}

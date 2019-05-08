#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <assert.h>
#include <fstream>

using namespace std;

#define rep(i, l, r) for(int i=l; i<=r; i++)
#define dow(i, l, r) for(int i=l; i>=r; i--)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define clr(x, c) memset(x,c,sizeof(x))

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> Pii;

inline int read()
{
	int x=0,f=0; char ch=getchar();
	while (ch<'0' || '9'<ch) f|=ch=='-', ch=getchar();
	while ('0'<=ch && ch<='9') x=x*10+ch-'0', ch=getchar();
	return f?-x:x;
}

ull c1, c2, e1, e2, N, m;

ull mult(ull a, ull b)
{
	ull g = 0;
	while (b)
	{
		if (b & 1) g = (g+a)%N;
		a = (a+a)%N; b >>= 1;
	}
	return g;
}

ull poww(ull a, ull b)
{
	ull g = 1;
	while (b)
	{
		if (b & 1) g = mult(g,a);
		a = mult(a,a); b >>= 1;
	}
	return g;
}

bool check()
{
	return (poww(m,e1)==c1) && (poww(m,e2)==c2);
}

int main()
{
	ifstream fin("2.in");
	ifstream fout("2.ans");
	int T;
	assert(fin >> T);
	rep(i, 1, T)
	{
		assert(fin >> c1 >> c2 >> e1 >> e2 >> N);
		assert(fout >> m);
		if (check() == false) cout << poww(m,e1) << ' ' << c1  << ' ' << i << endl;
	}
	cout << "OK";
	return 0;
}
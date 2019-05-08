#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define DFOR(i, x, y) for(int i = hd[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x7fffffff;
const int MOD = 1000000007;

template <typename tn>
inline tn read(){
	char ch; tn f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	tn x = ch - '0';
	while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
	return x * f;
}
template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }

const int N = 100000 + 5;
struct Edge{
	int nxt, to;
}e[N * 2];
int tot[N][2], num[2], hd[N], c[N][2], tail, type, Case;
LL ans;

void add(int x, int y){
	if (y >= x) printf("Wa!");
	e[++tail] = (Edge){hd[x], y}, hd[x] = tail;
	e[++tail] = (Edge){hd[y], x}, hd[y] = tail;
}
void color(int x, int f, int dis){
	if (dis < 0) return;
	c[x][type] = Case, ++num[type]; 
	DFOR(i, x, y) if (y != f) color(y, x, dis - 1);
}
void dfs(int x, int f, int dep){
	tot[x][0] = tot[x][1] = 0;
	DFOR(i, x, y) if (y != f){
		dfs(y, x, dep + 1);
		tot[x][0] += tot[y][0], tot[x][1] += tot[y][1];
		ans += (LL)dep * tot[y][0] * tot[y][1] * 2;
//		cout << x << '+' << tot[y][0] * tot[y][1] * 2 << endl;
	}
//	cout << x << '-' << tot[x][0] * tot[x][1] * 2 << endl;
	if (c[x][0] == Case) tot[x][0]++, ans += (LL)dep * num[1];
	if (c[x][1] == Case) tot[x][1]++, ans += (LL)dep * num[0];
	ans -= (LL)dep * tot[x][0] * tot[x][1] * 2;
//	cout << x << ' ' << tot[x][0] << ' ' << tot[x][1] << ' ' << dep << endl;
}
int main(){
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	
	int n = rint;
	REP(i, 2, n) add(i, rint);
	int m = rint;
	for (Case = 1; Case <= m; Case++){
		int p0 = rint, d0 = rint, p1 = rint, d1 = rint;
		if (p0 < 1 || p0 > n || p1 < 1 || p1 > n) printf("Wa!");
		ans = num[0] = num[1] = 0;
		type = 0, color(p0, 0, d0);
		type = 1, color(p1, 0, d1);
		dfs(1, 0, 0);
		printf("%lld\n", ans);
	}
}

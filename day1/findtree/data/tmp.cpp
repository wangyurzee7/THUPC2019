#include <bits/stdc++.h>
using namespace std;

namespace __main__ {

	const int MAX_N = 80;
	const int MAX_W = 12;
	const int MAX_V = 1 << MAX_W;
	const int mod = 64123;
	using ll = unsigned;

	int N, M, W;
	char opr[MAX_W + 1];
	int e[MAX_N][MAX_N][MAX_V], f[MAX_N][MAX_N], ans[MAX_V];

	constexpr int add(int x, int v) {return (x + v) >= mod ? x + v - mod : x + v;}
	constexpr int sub(int x, int v) {return x < v ? x - v + mod : x - v;}
	inline void Add(int &x, int v) {x += v; x >= mod ? x -= mod : 0;}
	inline void Sub(int &x, int v) {x -= v; x < 0 ? x += mod : 0;}

	template<bool d>
	void trans(int *f) {
		int V = 1 << W;
		for(int i = 0; i < W; ++i) {
			register int bit = 1 << i;
			switch(opr[i]) {
				case '|':
					for(register int s = 0; s < V; ++s)
						if(s & bit) (d ? Sub : Add)(f[s], f[s ^ bit]);

				break; case '&':
					for(register int s = 0; s < V; ++s)
						if(s & bit) (d ? Sub : Add)(f[s ^ bit], f[s]);

				break; case '^':
					for(register int s = 0, t, x, y; s < V; ++s)
						if(~s & bit) {
							t = s ^ bit;
							x = f[s]; y = f[t];
							f[s] = add(x, y);
							f[t] = sub(x, y);
						}
			}
		}
		if(d) {
			int x = 1;
			for(int i = 0; i < W; ++i) if(opr[i] == '^') 
				x = (ll) x * ((mod + 1) >> 1) % mod;
			if(x != 1) for(register int s = 0; s < V; ++s)
				f[s] = (ll) f[s] * x % mod;
		}
	}

	int inv(int x) {return x == 1 ? 1 : mod - (ll) (mod / x) * inv(mod % x) % mod;}

	int calc() {
		int ans = 1;
		for(int i = 1; i < N; ++i) {
			if(!f[i][i]) {
				int j = i;
				while(j < N && !f[j][i]) ++j;
				if(j >= N) return 0;
				for(int k = i; k < N; ++k) swap(f[i][k], f[j][k]);
				ans = sub(0, ans);
			}
			ans = (ll) ans * f[i][i] % mod;
			int t = inv(f[i][i]);
			for(int j = i + 1; j < N; ++j) if(f[j][i]) {
				int x = (ll) f[j][i] * t % mod;
				for(int k = i; k < N; ++k) Sub(f[j][k], (ll) f[i][k] * x % mod);
			}
		}
		return ans;
	}

	void __main__() {
		cin >> N >> M >> opr;
		W = strlen(opr);
		while(M--) {
			int x, y, v;
			cin >> x >> y >> v;
			if(x == y) continue;
			--x; --y;
			Sub(e[x][y][v], 1);
			Sub(e[y][x][v], 1);
			Add(e[x][x][v], 1);
			Add(e[y][y][v], 1);
		}
		for(int i = 0; i < N; ++i)
			for(int j = 0; j <= i; ++j) {
				trans<0>(e[i][j]);
				if(i > j) memcpy(e[j][i], e[i][j], (1 << W) << 2);
			}
		for(int v = 0; v < (1 << W); ++v) {
			for(int i = 0; i < N; ++i)
				for(int j = 0; j < N; ++j)
					f[i][j] = e[i][j][v];
			ans[v] = calc();
		}
		trans<1>(ans);
		for(int i = (1 << W); i--; ) if(ans[i]) {
			cout << i << endl;
			return;
		}
		cout << -1 << endl;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	__main__::__main__();
}
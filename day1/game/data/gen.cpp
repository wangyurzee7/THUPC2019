#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define down(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define bin(x) (1 << (x))
#define SZ(x) int((x).size()
// #define LX_JUDGE

using namespace std;
typedef pair<int, int> pii;
typedef vector<int> Vi;
typedef long long ll;

template<typename T> inline bool upmax(T &x, T y) { return x < y ? (x = y, 1) : 0; }
template<typename T> inline bool upmin(T &x, T y) { return x > y ? (x = y, 1) : 0; }

namespace MATH_CAL {
	int mod;
	inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
	inline int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
	inline int mul(int a, int b) { return (ll) a * b % mod; }
	inline void Add(int &a, int b) { (a += b) >= mod ? a -= mod : 0; }
	inline void Sub(int &a, int b) { (a -= b) < 0 ? a += mod : 0; }
	inline int qpow(int x, int n) { int r = 1; for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) r = mul(r, x); return r; }
	inline int mod_inv(int x) { return qpow(x, mod - 2); }
} using namespace MATH_CAL;

const int MAX_N = 3e5 + 10;

inline int Rand(int l, int r) { return rand() % (r - l + 1) + l; }

int prime[MAX_N], pcnt;
bool vis[MAX_N];

void sieve(int N) {
	rep (i, 2, N) {
		if (!vis[i]) {
			prime[pcnt++] = i;
		}
		rep (j, 0, pcnt) {
			int to = prime[j] * i;
			if (to >= N) break ;
			vis[to] = 1;
			if (i % prime[j] == 0) break ;
		}
	}
}

int A[MAX_N];

int main(int argc, char *argv[]) {

	int seed = atoi(argv[1]);
	srand(seed);
	sieve(201);
	int p = prime[Rand(0, pcnt - 1)];

	int n = 1;
	while (n * p <= int(3e5)) n *= p;

	rep (i, 0, n) A[i] = Rand(0, p - 1);

	int tm = Rand(0, 3000);

	while (tm--) {
		int x = A[0];
		rep (j, 0, n - 1) A[j] = (A[j] - A[j + 1] + p) % p;
		A[n - 1] = (A[n - 1] - x + p) % p;
	}

	int N = n * Rand(1, int(3e5) / n);
	rep (i, n, N) A[i] = A[i - n];

	rep (i, 0, N) A[i] = A[i] + p * Rand(0, 5000);

	printf("%d %d\n", N, p);
	rep (i, 0, N) printf("%d%c", A[i], " \n"[i == n - 1]);

	return 0;
}

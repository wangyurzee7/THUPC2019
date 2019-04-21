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

int fac[205], inv[205];
inline int nCr(int n, int r) { return n < r or r < 0 ? 0 : mul(fac[n], mul(inv[r], inv[n - r])); }
int N, P, A[MAX_N];

int main() {
#ifdef LX_JUDGE
	//freopen(".in", "r", stdin);
#endif

	int _N;
	scanf("%d%d", &_N, &P); mod = P;
	rep (i, 0, _N) {
		scanf("%d", &A[i]);
		A[i] %= P;
	}

	int N = 1;
	while (_N % (N * P) == 0) N *= P;

	rep (i, 0, _N - N) if (A[i] != A[i + N]) {
		puts("-1");
		return 0;
	}

	fac[0] = 1;
	rep (i, 1, P) fac[i] = mul(fac[i - 1], i);
	inv[P - 1] = mod_inv(fac[P - 1]);
	down (i, P, 1) inv[i - 1] = mul(inv[i], i);

	for (int i = 1; i < N; i *= P) {
		for (int j = 0; j < N; j += i * P) {
			for (int p = j; p < j + i; ++p) {
				for (int k = 0; k < P; ++k) {
					for (int l = k + 1; l < P; ++l) {
						Add(A[p + k * i], mul(nCr(l, k), A[p + l * i]));
					}
				}
			}
		}
	}

	int ans = 0;
	while (!A[ans] and ans < N) ++ans;

	printf("%d\n", N - ans);
	return 0;
}

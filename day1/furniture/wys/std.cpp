#include <stdio.h>
#include <string.h>

const int MAXN = 1000005;
const int MAXK = 19;
const int P = 998244353;
const int MAXT = P;
const int Q = 32000;

inline int pow(int a, int b) {
	int ret = 1;
	while (b--) ret *= a;
	return ret;
}

inline int powmod(int a, int b) {
	int ret = 1;
	while (b) {
		if (b & 1) ret = 1LL * ret * a % P;
		a = 1LL * a * a % P;
		b >>= 1;
	}
	return ret;
}

inline int inv(int a) {
	return powmod(a, P - 2);
}

int n, k, q;
int N;

struct Data {
	int a[MAXK + 1];
};

Data operator + (const Data &a, const Data &b) {
	Data ret;
	for (int i = 0; i <= k; i++) {
		ret.a[i] = (a.a[i] + b.a[i]) % P;
	}
	return ret;
}

Data operator - (const Data &a, const Data &b) {
	Data ret;
	for (int i = 0; i <= k; i++) {
		ret.a[i] = (a.a[i] + P - b.a[i]) % P;
	}
	return ret;
}

Data shift(const Data &a) {
	Data ret;
	ret.a[0] = 0;
	for (int i = 1; i <= k; i++) {
		ret.a[i] = a.a[i - 1];
	}
	return ret;
}

Data a[MAXN];
Data b[MAXN];

void magic(int base, Data *a, int N) {
	if (N == 1) {
		::b[base] = a[0];
		return;
	}
	
	int N1 = N / n;
	Data *b = new Data[N1];
	memset(b, 0, N1 * sizeof(Data));
	for (int i = 0; i < n; i++) {
		Data *ai = a + i * N1;
		for (int j = 0; j < N1; j++) {
			b[j] = b[j] + ai[j];
		}
	}
	for (int i = 0; i < N1; i++) {
		b[i] = shift(b[i]);
	}
	
	for (int i = 0; i < n; i++) {
		Data *ai = a + i * N1;
		for (int j = 0; j < N1; j++) {
			b[j] = b[j] - shift(ai[j]) + ai[j];
		}
		magic(base + i * N1, b, N1);
		for (int j = 0; j < N1; j++) {
			b[j] = b[j] + shift(ai[j]) - ai[j];
		}
	}
}

struct Matr {
	int a[MAXK + 1][MAXK + 1];
};

Matr operator * (const Matr &a, const Matr &b) {
	Matr ret;
	memset(&ret, 0, sizeof(ret));
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= k; j++) {
			unsigned long long tmp = 0;
			for (int kk = 0; kk <= k; kk++) {
				tmp += 1LL * a.a[i][kk] * b.a[kk][j];
			}
			ret.a[i][j] = tmp % P;
		}
	}
	return ret;
}

Matr trans1[Q + 1];
Matr transQ[Q + 1];

int invs[MAXK + 1];

void pre() {
	Matr A, I;
	memset(&A, 0, sizeof(A));
	memset(&I, 0, sizeof(I));
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= k; j++) {
			if (j == i) {
				I.a[i][j] = 1;
				A.a[i][j] = i * (n - 2);
			} else if (j == i - 1) {
				A.a[i][j] = i;
			} else if (j == i + 1) {
				A.a[i][j] = (k - i) * (n - 1);
			}
		}
	}
	
	trans1[0] = I;
	for (int i = 1; i <= Q; i++) {
		trans1[i] = trans1[i - 1] * A;
	}
	A = trans1[Q];
	
	transQ[0] = I;
	for (int i = 1; i <= Q; i++) {
		transQ[i] = transQ[i - 1] * A;
	}
	
	invs[0] = 1;
	for (int i = 1; i <= k; i++) {
		invs[i] = 1LL * invs[i - 1] * (k - i + 1) % P * inv(i) % P * (n - 1) % P;
	}
	for (int i = 1; i <= k; i++) {
		invs[i] = inv(invs[i]);
	}
}

int query(int x, int T) {
	const Matr &m1 = trans1[T % Q];
	const Matr &m2 = transQ[T / Q];
	
	int ret = 0;
	for (int i = 0; i <= k; i++) {
		unsigned long long tmp = 0;
		for (int j = 0; j <= k; j++) {
			tmp += 1LL * m1.a[0][j] * m2.a[j][i];
		}
		ret = (ret + tmp % P * b[x].a[i] % P * invs[i]) % P;
	}
	
	return ret;
}

int main() {
	scanf("%d%d%d", &n, &k, &q);
	N = pow(n, k);
	for (int i = 0; i < N; i++) {
		scanf("%d", a[i].a);
	}
	
	magic(0, a, N);
	pre();
	
	int last_ans = 1;
	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		int T = 1LL * b * last_ans % P;
		printf("%d\n", last_ans = query(a, T));
	}
}

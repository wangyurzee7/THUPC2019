#include <bits/stdc++.h>

#define MAXK 50

using namespace std;

const int P = 59393;

int fac[P], faci[P];

int add(int a, int b) { return (a + b) % P; }
int sub(int a, int b) { return (a - b + P) % P; }
int mul(unsigned int a, unsigned int b) { return a * b % P; }

int fpow(int a, int b)
{
    int c = 1;
    while (b) {
        if (b & 1)
            c = mul(c, a);
        a = mul(a, a);
        b >>= 1;
    }
    return c;
}

int inv(int a) { return fpow(a, P - 2); }

int binom(int n, int m) { return m > n ? 0 : mul(fac[n], mul(faci[m], faci[n - m])); }

int lucas(int n, int m)
{
    if (m == 0 && n == 0)
        return 1;
    return mul(binom(n % P, m % P), lucas(n / P, m / P));
}

struct Point {
    int r, c;
    Point(int r = 0, int c = 0) : r(r), c(c) {}

    bool operator < (const Point& p) const { return r == p.r ? c < p.c : r < p.r; }
    bool operator == (const Point& p) const { return r == p.r && c == p.c; }

};

Point obs[MAXK + 10];
int k;

istream& operator >> (istream& is, Point& p)
{
    is >> p.r >> p.c;
    return is;
}

int get_front(int n, int m)
{
    n--;
    m--;
    int lim = min(n, m), ret = 0;
    for (int i = 0; i <= lim; i++) {
        int cur = mul(lucas(n, i), lucas(n + m - i, n));
        ret = add(ret, cur);
    }
    return ret;
}

int get_all(int n, int m)
{
    n--;
    m--;
    int lim = min(n, m), ret = 0;
    for (int i = 0; i <= lim; i++) {
        int a = mul(lucas(n, i), lucas(n + 1 + m - i, n + 1));
        int b = mul(lucas(m, i), lucas(m + 1 + n - i, m + 1));
        ret = add(ret, 2 * (a + b));
    }
    return sub(ret, get_front(n + 1, m + 1));
}

bool vis[MAXK + 10];
int f[MAXK + 10];

int solve_front(int pos)
{
    int &ret = f[pos];
    if (vis[pos] == 0) {
        vis[pos] = 1;
        int n = obs[pos].r, m = obs[pos].c;
        ret = get_front(n, m);
        for (int i = 0; i < pos; i++) {
            if (obs[i].r <= n && obs[i].c <= m) {
                ret = sub(ret, mul(solve_front(i), get_front(n - obs[i].r + 1, m - obs[i].c + 1)));
            }
        }
    }
    return ret;
}

int solve_all(int n, int m)
{
    int ret = get_all(n, m);
    for (int i = 0; i < k; i++) {
        ret = sub(ret, mul(solve_front(i), get_all(n - obs[i].r + 1, m - obs[i].c + 1)));
    }
    return ret;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i < P; i++)
        fac[i] = mul(fac[i - 1], i);

    faci[P - 1] = inv(fac[P - 1]);
    for (int i = P - 2; i >= 0; i--)
        faci[i] = mul(faci[i + 1], i + 1);
}

int main()
{
    init();
    int n, m;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
        cin >> obs[i];
    sort(obs, obs + k);
    k = unique(obs, obs + k) - obs;
    for (int i = 0; i < k; i++) {
        assert(obs[i].r <= n);
        assert(obs[i].c <= m);
    }
    cout << solve_all(n, m) << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)

const int P = 998244353;
int s[20][1000007];

struct Matrix
{
    int a[20][20];
};
Matrix operator *(const Matrix &x, const Matrix &y)
{
    Matrix z;
    memset(&z, 0, sizeof(z));
    g(i, 0, 20) g(j, 0, 20) g(k, 0, 20) z.a[i][j] = (z.a[i][j] + (ll) x.a[i][k] * y.a[k][j]) % P;
    return z;
}
Matrix unit()
{
    Matrix z;
    memset(&z, 0, sizeof(z));
    g(i, 0, 20) z.a[i][i] = 1;
    return z;
}
Matrix qpow(const Matrix &m, int x)
{
    if(x == 0) return unit();
    if(x & 1) return qpow(m, x - 1) * m;
    Matrix r = qpow(m, x / 2); return r * r;
}
int qpow(int x, int y)
{
    if(y == 0) return 1;
    if(y & 1) return (ll) qpow(x, y - 1) * x % P;
    int r = qpow(x, y / 2); return (ll) r * r % P;
}
int C[20][20];

struct Vector
{
    int a[20];
};
Vector operator *(const Vector &v, const Matrix &m)
{
    Vector r;
    memset(&r, 0, sizeof(r));
    g(i, 0, 20) g(j, 0, 20) r.a[j] = (r.a[j] + (ll) v.a[i] * m.a[i][j]) % P;
    return r;
}
Vector pre[200007];
Matrix pre2[5007];

int main()
{
    int n, k, q; scanf("%d%d%d", &n, &k, &q);
    C[0][0] = 1;
    g(i, 1, 20)
    {
        C[i][0] = 1;
        g(j, 1, 20) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
    }
    g(i, 0, 20) f(j, 0, i) C[i][j] = qpow((ll) C[i][j] * qpow(n - 1, j) % P, P - 2);
    int N = 1;
    g(_, 0, k) N *= n;
    g(i, 0, N) scanf("%d", s[0] + i);
    int pd = 1;
    cerr << clock() << endl;
    g(d, 0, k)
    {
        g(i, 0, N) if(!(i / pd % n)) h(od, d, 0)
        {
            ll cs = 0;
            g(j, 0, n) cs += s[od][i + pd * j];
            cs = cs % P + P;
            g(j, 0, n) s[od + 1][i + pd * j] = (cs - s[od][i + pd * j] + s[od + 1][i + pd * j]) % P;
        }
        pd *= n;
    }
    // g(i, 0, N) f(d, 0, k) printf("s %d %d = %d\n", i, d, s[d][i]);
    
    cerr << clock() << endl;
    
    Matrix A; memset(&A, 0, sizeof(A));
    g(i, 0, 20)
    {
        if(i && i <= k) A.a[i][i - 1] = i;
        if(i < k) A.a[i][i + 1] = (k - i) * (n - 1);
        if(i >= 0 && i <= k) A.a[i][i] = i * (n - 2);
    }
    pre[0].a[0] = 1;
    f(i, 0, 200000) pre[i + 1] = pre[i] * A;
    pre2[0] = unit();
    cerr << clock() << endl;
    
    Matrix B = qpow(A, 200000);
    f(i, 0, 5000) pre2[i + 1] = pre2[i] * B;
    cerr << clock() << endl;
    
    int R = 1;
    while(q--)
    {
        int a, b; scanf("%d%d", &a, &b);
        int T = (ll) R * b % P;
        Vector r = pre[T % 200000] * pre2[T / 200000];
        int ans = 0;
        f(d, 0, k) ans = (ans + (ll) s[d][a] * r.a[d] % P * C[k][d]) % P;
        printf("%d\n", R = ans);
    }
    cerr << clock() << endl;
    return 0;
}

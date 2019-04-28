#include <bits/stdc++.h>

#define MAXN 500000

using namespace std;

using pii = pair<int, int>;
using LL = long long;

pii a[MAXN + 10], b[MAXN + 10];

bool operator < (const pii& a, const pii& b) { return (LL)a.first * b.second < (LL)a.second * b.first; }
bool operator == (const pii& a, const pii& b) { return (LL)a.first * b.second == (LL)a.second * b.first; }

int find(const pii& x, const pii* a, int n)
{
    int l = 1, r = n;
    for(;;) {
        int m = (l + r) >> 1;
        if (a[m] == x)
            return m;

        if (a[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
}

struct BIT {
    LL c[MAXN + 10], sum = 0;
    int n, bit;

    void init(int n)
    {
        this->n = n;
        bit = 0;
        while ((1 << (bit + 1)) <= n)
            bit++;

        memset(c, 0, sizeof(c));
    }

    void add(int x, int v)
    {
        sum += v;
        while (x <= n) {
            c[x] += v;
            x += x & -x;
        }
    }

    LL get_sum(int x)
    {
        LL ret = -sum;
        while (x) {
            // cerr << x << endl;
            ret += c[x] << 1;
            x -= x & -x;
        }
        return ret;
    }

    int get_pos()
    {
        int ret = 0;
        LL cur = -sum;
        for (int i = bit; i >= 0; i--) {
            int pos = ret | (1 << i);
            if (pos <= n && cur + 2 * c[pos] < 0) {
                cur += 2 * c[pos];
                ret = pos;
            }
        }

        return ret + 1;
    }
};

BIT bit_a, bit_b;

ostream& operator << (ostream& os, const pii& a)
{
    os << "(" << a.first << ", " << a.second << ")";
    return os;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i].first);
    }

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i].second);

    int tot = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first != 0) {
            if (a[i].first < 0) {
                a[i].first = -a[i].first;
                a[i].second = -a[i].second;
            }
            b[tot++] = a[i];
        }
    }

    sort(b, b + tot, [](pii a, pii b) {
        return a < b;
    });
    tot = unique(b, b + tot, [] (pii a, pii b) {
        return a == b;
    }) - b;

    bit_a.init(tot);
    bit_b.init(tot);

    LL val = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first != 0) {
            int id = ::find(a[i], b, tot);
            bit_a.add(id + 1, a[i].first);
            bit_b.add(id + 1, a[i].second);
        } else
            val += abs(a[i].second);

        int pos = bit_a.get_pos();
        LL k = bit_a.get_sum(pos);
        printf("%lf\n", val - k * (double)b[pos - 1].second / b[pos - 1].first + bit_b.get_sum(pos));
    }

    return 0;
}
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 500000 + 7;
typedef long long LL;
typedef pair<int, int> pii;

int n, tot;
pii a[MAXN], b[MAXN];
LL sum[MAXN << 3], sumb[MAXN << 3];

bool operator < (const pii& a, const pii& b)
{
    return 1ll * a.second * b.first > 1ll * a.first * b.second;
}

void add(int o, int l, int r, int sp, pii sv)
{
    sum[o] += sv.first;
    sumb[o] += sv.second;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (sp <= mid)  add(o << 1, l, mid, sp, sv);
    else    add(o << 1 | 1, mid + 1, r, sp, sv);
}

LL querya_sum(int o, int l, int r, int qp)
{
    if (r <= qp)    return sum[o];
    int mid = (l + r) >> 1;
    if (qp <= mid)  return querya_sum(o << 1, l, mid, qp);
    else    return sum[o << 1] + querya_sum(o << 1 | 1, mid + 1, r, qp);
}

LL queryb_sum(int o, int l, int r, int qp)
{
    if (r <= qp)    return sumb[o];
    int mid = (l + r) >> 1;
    if (qp <= mid)  return queryb_sum(o << 1, l, mid, qp);
    else    return sumb[o << 1] + queryb_sum(o << 1 | 1, mid + 1, r, qp);
}

int query_pos(int o, int l, int r, LL cur)
{
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (cur + 2ll * sum[o << 1] >= 0)
        return query_pos(o << 1, l, mid, cur);
    else
        return query_pos(o << 1 | 1, mid + 1, r, cur + 2ll * sum[o << 1]);
}

int search(const pii& x, const pii* a, int n)
{
    int L = 1, R = n + 1, Mid;
    while (L + 1 < R) {
        Mid = (L + R) >> 1;
        if (x < a[Mid]) R = Mid;
        else            L = Mid;
    }
    return L;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> a[i].first;
    for (int i = 1; i <= n; ++ i)
        cin >> a[i].second;
    for (int i = 1; i <= n; ++ i)
        if (a[i].first != 0) {
            if (a[i].first < 0) {
                a[i].first = -a[i].first;
                a[i].second = -a[i].second;
            }
            b[++tot] = a[i];
        }
    sort(b + 1, b + 1 + tot, [](pii a, pii b) {
        return a < b;
    });
    tot = unique(b + 1, b + 1 + tot, [](pii a, pii b) {
        return a.first * b.second == a.second * b.first;
    }) - b - 1;
    // for (int i = 1; i <= tot; ++ i)
    //     printf("%d %d\n", b[i].first, b[i].second);
    LL cons = 0ll;
    for (int i = 1; i <= n; ++ i) {
        if (a[i].first != 0) {
            int id = search(a[i], b, tot);
            add(1, 1, tot, id, a[i]);
        } else {
            cons += abs(a[i].second);
        }

        int pos = query_pos(1, 1, tot, -sum[1]);
        LL p = 2 * querya_sum(1, 1, tot, pos) - sum[1];
        printf("%lf\n", cons - (double)p * b[pos].second / b[pos].first
         + 2 * queryb_sum(1, 1, tot, pos) - sumb[1]);
    }
    return 0;
}

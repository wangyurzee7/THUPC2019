#include <cstdio>
#include <algorithm>
#include <list>
#include <vector>

static const int MAXM = 10000;
static const int MAXN = 501;

static int m;
static int n[MAXM], *a[MAXM];

static std::vector<int> vals;
static int valc;

static std::vector<int> diff[MAXM * MAXN];
static int t[MAXM];
static std::list<int> ts[MAXN * 2 + 1];
static std::list<int>::iterator itr[MAXM];

static int ans[MAXM] = { 0 };

int main()
{
    scanf("%d", &m);
    vals.reserve(m * MAXN);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &n[i]);
        a[i] = new int[n[i]];
        for (int j = 0; j < n[i]; ++j) {
            scanf("%d", &a[i][j]);
            vals.push_back(a[i][j]);
        }
    }

    // Discretization
    std::sort(vals.begin(), vals.end());
    valc = std::distance(vals.begin(), std::unique(vals.begin(), vals.end()));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n[i]; ++j) {
            a[i][j] = std::distance(
                vals.begin(),
                std::lower_bound(vals.begin(), vals.end(), a[i][j])
            );
            diff[a[i][j]].push_back(i);
        }

    for (int i = 0; i < m; ++i) t[i] = -n[i];

    /*for (int v = 0; v < valc; ++v) {
        for (int i : diff[v]) t[i] += 2;
        for (int i = 0; i < m; ++i)
            for (int j = i; j < m; ++j)
                if (t[i] + t[j] >= 0)
                    printf("%d | %d %d\n", vals[v], i, j);
    }*/

    for (int i = 0; i < m; ++i) {
        ts[MAXN - n[i]].push_back(i);
        itr[i] = ts[MAXN - n[i]].end();
        --itr[i];
    }

    for (int v = 0; v < valc; ++v) {
        for (int i : diff[v]) {
            ts[MAXN + t[i]].erase(itr[i]);
            t[i] += 2;
            ts[MAXN + t[i]].push_back(i);
            itr[i] = ts[MAXN + t[i]].end();
            --itr[i];
            /*if (t[i] == 1) printf("%d | %d %d\n", vals[v], i, i);
            for (int j : ts[MAXN - t[i] + 1])
                printf("%d | %d %d\n", vals[v], i, j);
            for (int j : ts[MAXN - t[i]])
                printf("%d | %d %d\n", vals[v], i, j);*/
            // t[i] == 0 is considered here, because
            // the answer will be updated twice in the loop below,
            // resulting in the change being cancelled out
            if (t[i] == 0 || t[i] == 1) ans[i] ^= (vals[v] + i + i + 2);
            for (int j : ts[MAXN - t[i] + 1]) {
                ans[i] ^= (vals[v] + i + j + 2);
                ans[j] ^= (vals[v] + i + j + 2);
            }
            for (int j : ts[MAXN - t[i]]) {
                ans[i] ^= (vals[v] + i + j + 2);
                ans[j] ^= (vals[v] + i + j + 2);
            }
        }
    }

    for (int i = 0; i < m; ++i) printf("%d\n", ans[i]);

    return 0;
}

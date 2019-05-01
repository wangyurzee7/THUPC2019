#include <cstdio>
#include <ctime>
#include <algorithm>
#include <list>
#include <tuple>
#include <vector>

#define SMALL 0

#if SMALL
static const int MAXM = 100;
#else
static const int MAXM = 10000;
#endif
static const int MAXN = 501;

static int m;
static int n[MAXM], *a[MAXM];

static std::vector<int> vals;
static std::vector<std::tuple<int, int, int *>> poss;

static std::vector<int> diff[MAXM * MAXN];
static int t[MAXM];
static std::list<int> ts[MAXN * 2 + 1];
static std::list<int>::iterator itr[MAXM];

static int ans[MAXM] = { 0 };

namespace fio {

static const int BUFSZ = 9876;
static char buf[BUFSZ];
static int bufptr = BUFSZ - 1;

inline void flush()
{
    fread(buf, BUFSZ, 1, stdin);
    bufptr = -1;
}

inline char getchar()
{
    if (bufptr == BUFSZ - 1) flush();
    return buf[++bufptr];
}

inline int read_int()
{
    char ch;
    int ret = 0;
    while ((ch = getchar()) < '0' || ch > '9') ;
    ret = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') ret = ret * 10 + ch - '0';
    return ret;
}

} // namespace fio

int main()
{
    m = fio::read_int();
    poss.reserve(m * MAXN);
    for (int i = 0; i < m; ++i) {
        n[i] = fio::read_int();
        a[i] = new int[n[i]];
        for (int j = 0; j < n[i]; ++j) {
            a[i][j] = fio::read_int();
            poss.push_back({a[i][j], i, &a[i][j]});
        }
    }
    fprintf(stderr, "%.4lf\n", (double)clock() / CLOCKS_PER_SEC);

    // Discretization
    std::sort(poss.begin(), poss.end(),
        [] (const std::tuple<int, int, int *> &a, const std::tuple<int, int, int *> &b) {
            return std::get<0>(a) < std::get<0>(b);
        });
    vals.reserve(poss.size());
    for (auto p : poss) {
        if (vals.empty() || std::get<0>(p) != vals.back())
            vals.push_back(std::get<0>(p));
        *std::get<2>(p) = vals.size() - 1;
        diff[vals.size() - 1].push_back(std::get<1>(p));
    }
    fprintf(stderr, "%.4lf\n", (double)clock() / CLOCKS_PER_SEC);

    for (int i = 0; i < m; ++i) t[i] = -n[i];

    for (int i = 0; i < m; ++i) {
        ts[MAXN - n[i]].push_back(i);
        itr[i] = ts[MAXN - n[i]].end();
        --itr[i];
    }

    for (int v = 0; v < vals.size(); ++v) {
        for (int i : diff[v]) {
            ts[MAXN + t[i]].erase(itr[i]);
            t[i] += 2;
            ts[MAXN + t[i]].push_back(i);
            itr[i] = ts[MAXN + t[i]].end();
            --itr[i];
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
    fprintf(stderr, "%.4lf\n", (double)clock() / CLOCKS_PER_SEC);

    for (int i = 0; i < m; ++i) printf("%d\n", ans[i]);

    return 0;
}

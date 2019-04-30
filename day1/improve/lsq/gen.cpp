#include "testlib.h"
#include <cstdio>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>

// ./gen <n> <m>

static const int MAXN = 2002;
static const int MAXM = 60003;

static int n, m;
static int c[MAXN];
static int w[MAXN];
static std::vector<int> e[MAXN];
static std::set<std::pair<int, int>> es;

inline bool add_edge(int u, int v)
{
    if (es.count({u, v})) return false;
    e[u].push_back(v);
    es.insert({u, v});
    return true;
}

void gen_random()
{
    c[0] = 0;
    for (int i = 1; i < n; ++i) c[i] = rnd.next(1, n - 1);
    for (int i = 0; i < n; ++i) w[i] = rnd.next(1, 100);
    for (int i = 0; i < m; ++i) {
        int u, v;
        do {
            u = rnd.next(n - 1);
            v = rnd.next(u + 1, n - 1);
        } while (!add_edge(u, v));
    }
}

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);

    n = strtol(argv[1], NULL, 10);
    m = strtol(argv[2], NULL, 10);

    gen_random();

    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
        printf("%d%c", c[i] + 1, i == n - 1 ? '\n' : ' ');
    for (int i = 0; i < n; ++i)
        printf("%d%c", w[i], i == n - 1 ? '\n' : ' ');
    // Randomly shuffle edges
    std::vector<std::pair<int, int>> ev;
    for (auto e : es) ev.push_back(e);
    shuffle(ev.begin(), ev.end());
    for (auto e : ev) printf("%d %d\n", e.first + 1, e.second + 1);

    return 0;
}

#include "testlib.h"
#include <cstdio>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>

// ./gen <type> <n> <m> [<n1> <m1> <n2> <m2>]
// <type>: linear/majime/broom/maxans

// Test runs:
// for i in {1..100}; do ./a.out linear 10 20 Seed=$i | python3 ../wyz.validate/vali.py; done
// for i in {1..100}; do ./a.out majime 30 40 15 20 5 10 Seed=$i | python3 ../wyz.validate/vali.py; done
// for i in {1..100}; do ./a.out broom 30 40 Seed=$i | python3 ../wyz.validate/vali.py; done

static const int MAXN = 2002;
static const int MAXM = 60003;

static int argc;
static int n, m, n1, m1, n2, m2;
static int c[MAXN];
static int w[MAXN];

struct edgeset {
    std::vector<int> e[MAXN];
    std::set<std::pair<int, int>> es;
    int indeg[MAXN];

    edgeset()
    {
        std::fill(indeg, indeg + MAXN, 0);
    }

    inline bool add_edge(int u, int v)
    {
        if (u == v || this->es.count({u, v})) return false;
        this->e[u].push_back(v);
        this->es.insert({u, v});
        indeg[v] += 1;
        return true;
    }

    inline std::vector<std::pair<int, int>> shuffled()
    {
        std::vector<std::pair<int, int>> ev;
        for (auto e : this->es) ev.push_back(e);
        //shuffle(ev.begin(), ev.end());
        return ev;
    }
};

static edgeset es;

template <typename T> inline T &rand_one(std::vector<T> &v)
{
    return v[rnd.next(v.size())];
}

inline void gen_dag(edgeset &es, int n0, int m0)
{
    int u, v;
    for (int i = 0; i < m0; ++i) {
        do {
            u = rnd.next(n0 - 1);
            v = rnd.next(u + 1, n0 - 1);
        } while (!es.add_edge(u, v));
    }
}

void gen_linear()
{
    for (int i = 0; i < n; ++i) c[i] = rnd.next(1, n - 1);
    for (int i = 0; i < n; ++i) w[i] = rnd.next(1, 100);
    gen_dag(es, n, m);
    for (int i = 0; i < n; ++i) if (es.indeg[i] == 0) c[i] = 0;
}

void gen_majimerand()
{
    ensuref(argc >= 8, "Insufficient number of arguments");

    // Generate DAG of SCCs
    static edgeset scc_es;
    gen_dag(scc_es, n1, m1);

    // Mark all no-in vertices
    std::vector<int> no_in;
    for (int i = 0; i < n1; ++i)
        if (scc_es.indeg[i] == 0) no_in.push_back(i);

    // Generate extra vertices for this DAG
    for (int i = 0; i < n2; ++i) {
        scc_es.add_edge(n1 + i, rand_one(no_in));
    }
    // ... and extra edges too
    for (int i = 0; i < m2 - n2; ++i) {
        int u, v;
        do {
            u = rnd.next(n1, n1 + n2 - 1);
            v = rnd.next(2) ?
                no_in[rnd.next(no_in.size())] :
                rnd.next(n1);
        } while (!scc_es.add_edge(u, v));
    }

    // Generate ear decomposition of SCCs
    std::vector<int> scc_vs[MAXN];
    for (int i = 0; i < n1 + n2; ++i) scc_vs[i].push_back(i);
    int n3 = n1 + n2;
    int m3 = m1 + m2;
    while (n3 <= n - 1 && m3 <= m - 2) {
        int scc_id = rnd.next(n1 + n2);
        int ni = rnd.wnext(1, std::min(n - n3, m - m3 - 1), -2);
        int u = rand_one(scc_vs[scc_id]);
        int v = rand_one(scc_vs[scc_id]);
        es.add_edge(u, n3);
        for (int i = 0; i < ni - 1; ++i) {
            scc_vs[scc_id].push_back(n3 + i);
            es.add_edge(n3 + i, n3 + i + 1);
        }
        scc_vs[scc_id].push_back(n3 + ni - 1);
        es.add_edge(n3 + ni - 1, v);
        n3 += ni;
        m3 += ni + 1;
    }
    n = n3;
    m = m3;

    // Connect SCCs
    for (int u = 0; u < n1 + n2; ++u)
        for (int v : scc_es.e[u]) {
            int x = rand_one(scc_vs[u]);
            int y = rand_one(scc_vs[v]);
            es.add_edge(x, y);
        }

    // Add information
    for (int i = 0; i < n; ++i) {
        c[i] = rnd.wnext(1, n - 1, -3);
        w[i] = rnd.wnext(1, 100, +3);
    }

    // Mark originally no-in SCCs
    for (int u : no_in) {
        int v = rand_one(scc_vs[u]);
        c[v] = 0;
        w[v] = rnd.wnext(1, 100, -5);
    }
}

void gen_broom()
{
    for (int i = 0; i < n / 2; ++i) es.add_edge(i, n / 2);
    for (int i = n / 2; i < n - 1; ++i) es.add_edge(i, i + 1);
    for (int i = n - 1; i < m; ++i) {
        int u, v;
        do {
            u = rnd.next(n / 2, n - 1);
            v = rnd.next(n / 2, n - 1);
        } while (!es.add_edge(u, v));
    }
    for (int i = 0; i < n / 2; ++i) {
        c[i] = 0;
        w[i] = rnd.wnext(1, 100, -6);
    }
    for (int i = n / 2; i < m; ++i) {
        c[i] = rnd.wnext(1, n - 1, -3);
        w[i] = rnd.next(1, 100);
    }
}

void gen_maxans()
{
    c[0] = 0;
    for (int i = 1; i < n; ++i) c[i] = 1;
    w[0] = 1;
    for (int i = 1; i < n; ++i) w[i] = 100;
    for (int i = 0; i < n - 1; ++i) es.add_edge(i, i + 1);
}

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    ::argc = argc;

    n = strtol(argv[2], NULL, 10);
    m = strtol(argv[3], NULL, 10);
    n1 = (argc >= 5 ? strtol(argv[4], NULL, 10) : -1);
    m1 = (argc >= 6 ? strtol(argv[5], NULL, 10) : -1);
    n2 = (argc >= 7 ? strtol(argv[6], NULL, 10) : -1);
    m2 = (argc >= 8 ? strtol(argv[7], NULL, 10) : -1);

    if (strcmp(argv[1], "linear") == 0)
        gen_linear();
    else if (strcmp(argv[1], "majime") == 0)
        gen_majimerand();
    else if (strcmp(argv[1], "broom") == 0)
        gen_broom();
    else if (strcmp(argv[1], "maxans") == 0)
        gen_maxans();
    else { puts("> <"); return 1; }

    m = es.es.size();
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
        printf("%d%c", c[i] + 1, i == n - 1 ? '\n' : ' ');
    for (int i = 0; i < n; ++i)
        printf("%d%c", w[i], i == n - 1 ? '\n' : ' ');
    for (auto e : es.shuffled()) printf("%d %d\n", e.first + 1, e.second + 1);

    return 0;
}

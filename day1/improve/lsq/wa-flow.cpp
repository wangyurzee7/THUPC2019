// Wrong Answer / Time Limit Exceeded:
// Fractional programming + maximum closed subgraph solution
// Expect bugs, typos and incorrect assumptions.
// Gives a wrong answer even on the sample, but including it here anyway

#include <cstdio>
#include <algorithm>
#include <vector>

static const int MAXN = 2002;
static const int MAXM = 60003;
static const int MAXW = 100;
static const int MAXANS = MAXN * MAXW;

static int n, m;
static int c[MAXN];
static int w[MAXN];
static std::vector<int> e[MAXN];

// Graph with shrinked SCCs
static int nn;
static std::vector<int> g[MAXN];

// sccw[SCC index][member index] - total time of a member in an SCC
static int sccw[MAXN][MAXN] = {{ 0 }};

namespace scc {

std::vector<int> re[MAXN];  // Reversed graph
std::vector<int> dfr;       // Ordered route of depth-first traversal
bool vis[MAXN] = { false };
int sccid[MAXN];
int scccnt = 0;

void dfs(int u)
{
    vis[u] = true;
    for (int v : e[u]) if (!vis[v]) dfs(v);
    dfr.push_back(u);
}

void rdfs(int u)
{
    vis[u] = true;
    sccid[u] = scccnt;
    for (int v : re[u]) if (!vis[v]) rdfs(v);
}

void shrink()
{
    for (int u = 0; u < n; ++u) for (int v : e[u]) re[v].push_back(u);
    for (int u = 0; u < n; ++u) if (!vis[u]) dfs(u);
    std::fill(vis, vis + n, false);
    std::reverse(dfr.begin(), dfr.end());
    for (int u : dfr) if (!vis[u]) { rdfs(u); ++scccnt; }
    for (int u = 0; u < n; ++u) sccw[sccid[u]][c[u]] += w[u];
    for (int u = 0; u < n; ++u) for (int v : e[u])
        if (sccid[u] != sccid[v]) g[sccid[u]].push_back(sccid[v]);
    for (int i = 0; i < scccnt; ++i) {
        std::sort(g[i].begin(), g[i].end());
        g[i].resize(std::unique(g[i].begin(), g[i].end()) - g[i].begin());
    }
}

} // namespace scc

// https://loj.ac/submission/6433

namespace nwf {

static const int MAXN = ::MAXN + 2;
static const int INF = 0x3fffffff;

int n, source, sink;
struct edge {
    int dest, cap, resi;
    edge() { }
    edge(int dest, int cap, int resi)
        : dest(dest), cap(cap), resi(resi) { }
};
std::vector<edge> e[MAXN];

inline void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i) e[i].clear();
}

inline std::vector<edge>::iterator add_edge(int u, int v, int c, int r = 0) {
    e[u].push_back(edge(v, c, e[v].size()));
    e[v].push_back(edge(u, r, e[u].size() - 1));
    return e[v].end() - 1;
}

int lim;
int d[MAXN];

inline bool level_graph() {
    static int q[MAXN], qhead, qtail;
    for (int i = 0; i < n; ++i) d[i] = -1;
    d[source] = 0, q[0] = source, qhead = 0, qtail = 1;

    while (qhead < qtail) {
        int u = q[qhead++];
        for (std::vector<edge>::iterator w = e[u].begin(); w != e[u].end(); ++w)
            if (w->cap >= lim && d[w->dest] == -1) {
                d[w->dest] = d[u] + 1;
                q[qtail++] = w->dest;
            }
    }

    return (d[sink] >= 0);
}

int cur[MAXN];

inline int augment(int u, int cur_cap) {
    if (u == sink) return cur_cap;
    int new_cap;
    for (int &i = cur[u]; i < e[u].size(); ++i) {
        edge &w = e[u][i];
        if (w.cap >= lim && d[w.dest] == d[u] + 1 &&
            (new_cap = augment(w.dest, std::min(w.cap, cur_cap))) >= lim)
        {
            w.cap -= new_cap;
            e[w.dest][w.resi].cap += new_cap;
            return new_cap;
        }
    }
    return 0;
}

// TODO: Try different strategies
// e.g. no binary scaling and break on reaching a given value
inline int deluge() {
    int ans = 0, aug;
    for (lim = 1 << 22; lim > 0; lim >>= 1) {
        while (level_graph()) {
            for (int i = 0; i < n; ++i) cur[i] = 0;
            while ((aug = augment(source, INF)) > 0) ans += aug;
        }
    }
    return ans;
}

} // namespace nwf

bool feasible(int ans)
{
    //printf("== ans %d ==\n", ans);
    nwf::source = nn;
    nwf::sink = nn + 1;
    // TODO: Avoid repeated graph building
    for (int i = 1; i < n; ++i) {
        nwf::init(nn + 2);
        for (int u = 0; u < nn; ++u)
            for (int v : g[u]) {
                nwf::add_edge(u, v, nwf::INF);
                //printf("%d %d inf\n", u, v);
            }
        int tot = 0;
        for (int u = 0; u < nn; ++u) {
            int val = sccw[u][i] - sccw[u][0] * ans;
            if (val > 0) {
                nwf::add_edge(nwf::source, u, val);
                //printf("src %d %d\n", u, val);
                tot += val;
            } else {
                nwf::add_edge(u, nwf::sink, -val);
                //printf("%d snk %d\n", u, -val);
            }
        }
        //printf(">> %d ", tot);
        tot -= nwf::deluge();
        //printf("%d\n", tot);
        // FIXME: Returns floor(ans + eps) instead of floor(ans)?
        if (tot == 0) return true;
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) { scanf("%d", &c[i]); --c[i]; }
    for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
    for (int i = 0, u, v; i < m; ++i) {
        scanf("%d%d", &u, &v); --u; --v;
        e[u].push_back(v);
    }

    scc::shrink();
    nn = scc::scccnt;
    // FIXME: Remove vertices unreachable from Z's vertices
    /*for (int i = 0; i < n; ++i)
        printf("%d%c", scc::sccid[i], i == n - 1 ? '\n' : ' ');
    for (int i = 0; i < nn; ++i)
        for (int j = 0; j < n; ++j)
            printf("%d%c", sccw[i][j], j == n - 1 ? '\n' : ' ');*/

    int lo = 0, hi = MAXANS, mid;
    while (lo < hi - 1) {
        mid = (lo + hi) >> 1;
        if (feasible(mid)) lo = mid; else hi = mid;
    }

    printf("%d\n", lo);
    return 0;
}

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

static const int MAXN = 2002;
static const int MAXM = 60003;

static int n, m;
static int c[MAXN];
static int w[MAXN];
static std::vector<int> e[MAXN];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) { scanf("%d", &c[i]); --c[i]; }
    for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
    for (int i = 0, u, v; i < m; ++i) {
        scanf("%d%d", &u, &v); --u; --v;
        e[u].push_back(v);
    }

    int ans = 0;
    bool vis[n];
    int tot[n];
    for (int i = 0; i < n; ++i) if (c[i] == 0) {
        std::fill(vis, vis + n, false);
        std::fill(tot, tot + n, 0);
        std::queue<int> q;
        tot[0] = w[i];
        q.push(i);
        vis[i] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : e[u]) if (!vis[v]) {
                tot[c[v]] += w[v];
                q.push(v);
                vis[v] = true;
            }
        }
        // Wrong Answer: May give an answer of 1 when 0 is expected
        for (int j = 0; j < n; ++j) ans = std::max(ans, tot[j] / w[i]);
    }

    printf("%d\n", ans);
    return 0;
}

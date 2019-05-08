#include<cstdio>
#include<cstdlib>
#include<queue>
#include<algorithm>

#define N 555
#define E 111111
#define INF 1111111111

using namespace std;

int tote, ss, tt;
int h[N], dis[N], pre[N], x[N], s[N], t[N];
bool inq[N];

struct edge {
    int f, t, v, w, n;
}e[E];

void add(int f, int t, int v, int w) {
    e[++tote].f = f;
    e[tote].t = t;
    e[tote].v = v;
    e[tote].w = w;
    e[tote].n = h[f];
    h[f] = tote;
    return ;
}

void adde(int f, int t, int v, int w) {
    add(f, t, v, w);
    add(t, f, 0, -w);
    return ;
}

bool spfa() {
    queue<int> Q;
    for (int i = 0; i < N; i++) dis[i] = -INF, inq[i] = false;
    dis[ss] = 0; Q.push(ss); inq[ss] = true;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop(); inq[u] = false;
        for (int i = h[u]; i != -1; i = e[i].n)
        if (e[i].v > 0) {
            int v = e[i].t;
            if (dis[v] < dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                pre[v] = i;
                if (!inq[v]) {
                    inq[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    return dis[tt] != -INF;
}

int cost_flow() {
    int tmp = 0, delta = INF, u = tt;
    while (u != ss) {
        delta = min(e[pre[u]].v, delta);
        tmp += e[pre[u]].w;
        u = e[pre[u]].f;
    }
    u = tt;
    while (u != ss) {
        e[pre[u]].v -= delta;
        e[pre[u] ^ 1].v += delta;
        u = e[pre[u]].f;
    }
    return delta * tmp;
}

void Solve() {
    for (int i = 0; i < N; i++) h[i] = -1;
    tote = -1;
    ss = 0; tt = N - 1;
    int n, a, b, ans = 0;
    double p;
    scanf("%d%d%d%lf", &n, &a, &b, &p);
    adde(ss, 1, a, 0);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &x[i], &s[i], &t[i]);
        ans += x[i];
        adde(1, i + 1, 1, 0);
        adde(i + 1, i + n + 1, 1, x[i]);
        adde(i + n + 1, tt, 1, 0);
    }
    bool legal = true;
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) 
            if (s[j] <= s[i] && t[j] - 1 >= s[i]) cnt++;
        if (cnt > a + b) legal = false;
    }
    if (!legal) {
        printf("impossible\n");
        return ;
    }
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++)
            if (i != j) {
                if (t[i] <= s[j]) adde(i + n + 1, j + 1, 1, 0);
                else if (s[i] < s[j]) adde(i + n + 1, j + 1, 1, -(int)(p * x[i] + 1e-3));
            }
    while (spfa()) ans -= cost_flow();
    printf("%d\n", ans);
    return ;
}

int main() {
    int test_case;
    scanf("%d", &test_case);
    for (int i = 1; i <= test_case; i++) Solve();
    return 0;
}
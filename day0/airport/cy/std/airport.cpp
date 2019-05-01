#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T, T INF, int MAXN, int MAXM>
struct MaxFlowMinCost
{
    int s, t, n;
    int head[MAXN], head2[MAXN], next[MAXM*2], to[MAXM*2], c[MAXM*2], op;
    T w[MAXM*2];
    T dis[MAXN];
    int used[MAXN], from[MAXN], way[MAXN], stop;
    T ans;

    void init(int s, int t, int n)
    {
        this->s = s;
        this->t = t;
        this->n = n;

        memset(head, 0, sizeof(head));
        op = 1;
        stop = 0;
    }
    void build(int u, int v, int c, T w)
    {
        next[++op] = head[u]; head[u] = op; to[op] = v; this->w[op] = w; this->c[op] = c;
        next[++op] = head[v]; head[v] = op; to[op] = u; this->w[op] = -w; this->c[op] = 0;
    }
    bool spfa()
    {
        memset(used, 0, sizeof(used));
        for(int i = 0; i <= n; i ++)
        {
            dis[i] = INF;
        }
        dis[s] = 0;
        from[s] = 0;

        queue<int> que;
        que.push(s);

        while(!que.empty())
        {
            int u = que.front(); que.pop();
            used[u] = 0;
            for(int pos = head[u]; pos; pos = next[pos])
                if(c[pos] && dis[to[pos]]>dis[u]+w[pos])
                {
                    from[to[pos]] = pos;
                    dis[to[pos]] = dis[u]+w[pos];
                    if (!used[to[pos]])
                    {
                        used[to[pos]] = 1;
                        que.push(to[pos]);
                    }
                }
        }
        memcpy(head2, head, sizeof(head));

        return dis[t] < INF;
    }
    T solve()
    {
        ans = 0;
        while(spfa())
        {
            int minflow = 0x7fffffff/2;
            for(int p = t; p != s; p = to[from[p]^1])
                minflow = min(minflow, c[from[p]]);
            for(int p = t; p != s; p = to[from[p]^1])
            {
                ans += minflow*w[from[p]];
                c[from[p]] -= minflow;
                c[from[p]^1] += minflow;
            }
        }
        return ans;
    }
    // bool dfs(int u, int top)
    // {
    //     if (u == t)
    //     {
    //         int minflow = 0x7fffffff/2;
    //         for(int i = top-1; i >= 1; i --)
    //             if (minflow >= c[way[i]])
    //             {
    //                 stop = i;
    //                 minflow = c[way[i]];
    //             }
    //         for(int i = 1; i < top; i ++)
    //         {
    //             ans += minflow*w[way[i]];
    //             c[way[i]] -= minflow;
    //             c[way[i]^1] += minflow;
    //         }
    //         return true;
    //     }
    //     used[u] = 1;
    //     for(int&pos = head2[u]; pos; pos = next[pos])
    //         if(c[pos] && dis[to[pos]] == dis[u] + w[pos] && !used[to[pos]])
    //         {
    //             way[top] = pos;
    //             if (dfs(to[pos], top+1) && top != stop)
    //             {
    //                 used[u] = 0;
    //                 return true;
    //             }
    //         }
    //     used[u] = 0;
    //     return false;
    // }
    // T solve()
    // {
    //     ans = 0;
    //     while(spfa())
    //     {
    //         memset(used, 0, sizeof(used));
    //         dfs(s, 1);
    //     }
    //     return ans;
    // }
};

bool extra_info = false;

namespace Solve
{
    const int MAXN = 2000 + 10;

    MaxFlowMinCost<int, 0x7fffffff/2, MAXN*4, MAXN*6> flow;
    int n, a, b;
    double p;
    int x[MAXN], s[MAXN], t[MAXN];
    int points[MAXN*3], cnt, sum[MAXN*3];

    void solve()
    {
        scanf("%d%d%d", &n, &a, &b);
        scanf("%lf", &p);
        cnt = 0;
        for(int i = 1; i <= n; i ++)
        {
            scanf("%d%d%d", &x[i], &s[i], &t[i]);
            points[++cnt] = s[i];
            points[++cnt] = s[i]+1;
            points[++cnt] = t[i];
        }

        sort(points+1, points+1+cnt);
        cnt = unique(points+1, points+1+cnt) - points - 1;
        for(int i = 1; i <= n; i ++)
        {
            s[i] = lower_bound(points+1, points+1+cnt, s[i]) - points;
            t[i] = lower_bound(points+1, points+1+cnt, t[i]) - points;
        }

        // check impossible
        memset(sum, 0, sizeof(sum));
        for(int  i = 1; i <= n; i ++)
        {
            sum[s[i]] ++;
            sum[t[i]] --;
        }
        for(int i = 1; i <= cnt; i ++)
        {
            sum[i] += sum[i-1];
            if (sum[i] > a+b)
            {
                puts("impossible");
                return;
            }
        }

        const int S = cnt + 1;
        const int T = cnt + 2;
        const int N = T + n;
        flow.init(S, T, N);

        flow.build(S, 1, a, 0);
        flow.build(cnt, T, a, 0);
        for(int i = 1; i < cnt; i ++)
        {
            flow.build(i, i+1, a, 0);
        }
        for(int i = 1; i <= n; i ++)
        {
            flow.build(s[i], T+i, 1, 0);
            flow.build(T+i, t[i], 1, -x[i]);
            flow.build(T+i, s[i]+1, 1, -(x[i]-floor(p*x[i]+1e-5)));
        }

        int ans = flow.solve();
        for(int i = 1; i <= n; i ++)
        {
            ans += x[i];
        }

        cout << ans << endl;
    }
}

int main(int argc, char* argv[])
{
#ifdef __TEST__
    freopen("airport.in", "r", stdin);
    freopen("airport.out", "w", stdout);
    extra_info = argc > 1;
#endif

    int T = 0;
    scanf("%d", &T);
    if (extra_info) cout << "T : " << T << endl;
    while(T --)
    {
        Solve::solve();
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 7;
int n;
double a[MAXN], b[MAXN], xpos[MAXN], ans[MAXN];
bool flag[MAXN];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> a[i];
    for (int i = 1; i <= n; ++ i)
        cin >> b[i];
    for (int i = 1; i <= n; ++ i) {
        xpos[i] = -b[i] / a[i];
        if (a[i] < 0) {
            a[i] = -a[i];
            b[i] = -b[i];
        }
        ans[i] = 1e30;
    }
    for (int i = 1; i <= n; ++ i) {
        double aa = 0, bb = 0;
        for (int j = 1; j < i; ++ j) {
            if (xpos[j] < xpos[i])
                aa += a[j], bb += b[j];
            else
                aa -= a[j], bb -= b[j];
        }
        for (int j = i; j <= n; ++ j) {
            if (xpos[j] < xpos[i])
                aa += a[j], bb += b[j];
            else
                aa -= a[j], bb -= b[j];
            ans[j] = min(ans[j], aa * xpos[i] + bb);
        }
        printf("%lf\n", ans[i]);   
    }
    return 0;
}
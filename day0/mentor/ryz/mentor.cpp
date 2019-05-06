#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

const int mod = 998244353;

struct school {
  int b,s,p;
} a[1001];
vector<school*> city[1001];
int sums[1001];

int f[2][3001][501],g[3005],sumg[3005],n,c,k,sumd,c0,c1,d0,d1,mc,md;
int t[501];

int main() {
#ifndef __TUACK__
  freopen("mentor.in","r",stdin);
  freopen("mentor.out","w",stdout);
#endif
int T;scanf("%d",&T);
while (T--){
  scanf("%d%d",&n,&c);
  scanf("%d%d%d%d",&c0,&c1,&d0,&d1);
  for (int i = 0;i < c;i++) {
    city[i].clear();
    sums[i] = 0;
  }
  for (int i = 0;i < n;i++) {
    scanf("%d%d",&a[i].b,&a[i].s);
    a[i].p = 0;
    city[a[i].b - 1].push_back(a + i);
    sums[a[i].b - 1] += a[i].s;
  }
  scanf("%d",&k);
  for (int j = 0,i,_p;j < k;j++) {
      scanf("%d%d",&i,&_p);
      a[i - 1].p=_p + 1;
  }
  memset(g,0,sizeof g);
  g[0] = 1;
  for (int i = 0;i < n;i++)
    if (!a[i].p)
      for (int j = d0;j >= a[i].s;j--) {
        g[j] += g[j - a[i].s];
        if (g[j] >= mod)
        g[j] -= mod;
      }
  sumg[0] = 0;
  for (int i = 1;i <= d0 + 1;i++) sumg[i] = (sumg[i - 1] + g[i - 1]) % mod;
  int now = 0,last = 1,temp = 2;
  memset(f,0,sizeof f);
  f[last][0][0] = 1;
  int sum = 0,sumd = 0,sumtemp,sumdtemp;
  for (int i = 0;i < c;i++)
    if (city[i].size() > 0) {
      sum += sums[i];
      int st = max(0,sum - c1),ed = min(sum,c0);
      for (int j = st;j <= ed;j++) {
        //blue
        memset(t,0,sizeof t);
        sumdtemp = sumd;
        if (j >= sums[i]) {
          for (int k = 0;k <= sumdtemp;k++) t[k] = f[last][j - sums[i]][k];
          for (int l = 0;l < city[i].size();l++) 
            if (city[i][l]->p > 0) {
              sumdtemp += city[i][l]->s;
              for (int k = sumdtemp;k >= 0;k--)
                  if (city[i][l]->p == 2) {
                    if (k >= city[i][l]->s) t[k] = t[k - city[i][l]->s];
                    else t[k] = 0;
                  }
                  else if (city[i][l]->p != 1 && k >= city[i][l]->s) {
                    t[k] += t[k - city[i][l]->s];
                    if (t[k] >= mod) t[k] -= mod;
                  }
            }
        }
        else for (int l = 0;l < city[i].size();l++) 
          if (city[i][l]->p > 0)
            sumdtemp += city[i][l]->s;
        for (int k = 0;k <= sumdtemp;k++) f[now][j][k] = t[k];
        //red      
        sumdtemp = sumd;
        memset(t,0,sizeof t);
      
        for (int k = 0;k <= sumdtemp;k++) t[k] = f[last][j][k];
        for (int l = 0;l < city[i].size();l++) 
          if (city[i][l]->p > 0) {
            sumdtemp += city[i][l]->s;
            for (int k = sumdtemp;k >= 0;k--)
                if (city[i][l]->p == 4) {
                  if (k >= city[i][l]->s) t[k] = t[k - city[i][l]->s];
                  else t[k] = 0;
                }
                else if (city[i][l]->p != 3 && k >= city[i][l]->s) {
                  t[k] += t[k - city[i][l]->s];
                  if (t[k] >= mod) t[k] -= mod;
                }
          }
        for (int k = 0;k <= sumdtemp;k++) {
          f[now][j][k] += t[k];
          if (f[now][j][k] >= mod)
            f[now][j][k] -= mod;
        }
      }
      sumd = sumdtemp;
      last = 1 - last;
      now = 1 - now;
    }
  int ans = 0;
  int st = max(0,sum - c1),ed = min(sum,c0);
  for (int i = st;i <= ed;i++)
    for (int j = 0;j <= sumd;j++)
        if (sum - d1 - j <= d0 - j) {
          int s1 = d0 - j + 1;
          if (s1 < 0) s1 = 0;
          int s2 = sum - d1 - j;
          if (s2 < 0) s2 = 0;
          ans += (((long long)f[last][i][j]) * (sumg[s1] - sumg[s2] + mod)) % mod;
          if (ans >= mod) ans -= mod;
        }
  printf("%d\n",ans);
}
  return 0;
}


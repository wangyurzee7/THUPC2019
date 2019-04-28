#include <bits/stdc++.h>
using namespace std;
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)

const int P = 998244353;

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        printf("usage: %s n k q\n", argv[0]);
        exit(1);
    }
    int n, k, q;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &k);
    sscanf(argv[3], "%d", &q);
    printf("%d %d %d\n", n, k, q);
    mt19937_64 rng(n * 233 + k * 666 + q);
    int N = 1;
    g(_, 0, k) N *= n;
    assert(N <= 1000000);
    g(i, 0, N) printf("%d\n", (int) (rng() % P));
    g(i, 0, q) printf("%d %d\n", (int) (rng() % N), (int) (rng() % P));
    return 0;
}

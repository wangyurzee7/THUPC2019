#include "../../../testlib/testlib.h"
#include "../cy/parse.hpp"

#include <cmath>
#include <algorithm>

using namespace std;

#define USAGE_MSG "./random -T T -maxn maxn -maxab maxab -maxx maxx -maxst maxst [--seed seed]"

// return true if OK
bool check(int n, int* S, int* T, int Q)
{
    int* list = new int[n*2+1];
    int cnt = 0;
    int* sum = new int[n*2+1];
    bool flag = true;

    for(int i = 1; i <= n; i ++)
    {
        list[++cnt] = S[i];
        list[++cnt] = T[i];
    }
    sort(list+1, list+1+cnt);
    cnt = unique(list+1, list+1+cnt) - list - 1;

    memset(sum, 0, sizeof(int)*(n*2+1));
    for(int i = 1; i <= n; i ++)
    {
        sum[lower_bound(list+1, list+1+cnt, S[i])-list] ++;
        sum[lower_bound(list+1, list+1+cnt, T[i])-list] --;
    }

    for(int i = 1; i <= cnt && flag; i ++)
    {
        sum[i] += sum[i-1];
        if (sum[i] > Q) flag = false;
    }

    delete[] list;
    delete[] sum;
    return flag;
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    map<string, char*> args = parseArgs(argc, argv);
    
    CHECK_OR_EXIT(args.find("T") != args.end());
    CHECK_OR_EXIT(args.find("maxn") != args.end());
    CHECK_OR_EXIT(args.find("maxab") != args.end());
    CHECK_OR_EXIT(args.find("maxx") != args.end());
    CHECK_OR_EXIT(args.find("maxst") != args.end());

    const int T = atoi(args["T"]);
    const int maxn = atoi(args["maxn"]);
    const int maxab = atoi(args["maxab"]);
    const int maxx = atoi(args["maxx"]);
    const int maxst = atoi(args["maxst"]);

    cout << T << endl;
    for(int kase = 1; kase <= T; kase ++)
    {
        const int n = rnd.next(int(maxn*0.8), maxn);
        const int a = rnd.next(int(maxab*0.8), maxab);
        const int b = rnd.next(int(maxab*0.8), maxab);
        cout << n << " " << a << " " << b << endl;
        cout << round(rnd.next(1.0)*100)/100.0 << endl;

        bool impossible = rnd.next(1.0)*T <= 2;

        int* S = new int[n+1];
        int* T = new int[n+1];

        int times = 0;
        while(true)
        {
            for(int i = 1; i <= n; i ++)
            {
                int s = rnd.next(1, maxst);
                int t = rnd.next(1, maxst);
                do {
                    if (s < t) {
                        if (rnd.next(1.0)<0.2 && double(t-s)/maxst<double(a+b)/n) break;
                        if (rnd.next(1.0)<exp(-n*double(t-s)/maxst)) break;
                    }
                    s = rnd.next(1, maxst);
                    t = rnd.next(1, maxst);
                } while(true);

                S[i] = s;
                T[i] = t;
            }

            if (impossible || check(n, S, T, a+b)) break;
            if (rnd.next(1.0) > exp(-double(times)/1000000.0)) break;
            times ++;
        }

        for(int i = 1; i <= n; i ++)
        {
            cout << rnd.next(1, maxx) << " " << S[i] << " " << T[i] << endl;
        }

        delete[] S;
        delete[] T;
    }

    return 0;
}
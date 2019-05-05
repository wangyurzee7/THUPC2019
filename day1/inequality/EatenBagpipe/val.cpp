#include <bits/stdc++.h>
#include <string>
using namespace std;

double eps = 1e-8;

bool equal(double x)
{
    return fabs(x) < eps;
}

int main()
{
    FILE *input;
    for (int i = 6; i <= 6; ++ i) {
        string file_in = string("../data/") + to_string(i) + string(".in");
        string file_out = string("../data/") + to_string(i) + string(".ans");
        // input = fopen(file_in.c_str(), "r");
        // int n;
        // double a, b;
        // fscanf(input, "%d", &n);
        // assert(n <= 500000);
        // for (int _ = 0; _ < n; ++ _) {
        //     fscanf(input, "%lf", &a);
        //     assert(equal(a) || equal(fabs(a)-1e9) || (fabs(a) > 0 && fabs(a) < 1e9));
        // }
        // for (int _ = 0; _ < n; ++ _) {
        //     fscanf(input, "%lf", &b);
        //     assert(equal(b) || equal(fabs(b)-1e9) || (fabs(b) > 0 && fabs(b) < 1e9));
        // }
        // fclose(input);
        string syscall = string("./100 < ") + file_in + string(" > ") + to_string(i) + string(".out");
        system(syscall.c_str());
        cerr << "Case " << i << ":" << endl;
        system((string("diff " + to_string(i) + string(".out ") + file_out)).c_str());
    }
    return 0;
}
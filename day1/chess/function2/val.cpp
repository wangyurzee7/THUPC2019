#include <bits/stdc++.h>
#include "testlib.h"


int main(int argc, char* argv[])
{
    registerValidation(argc, argv);
    int n = inf.readInt(1, 1000000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 50, "k");
    inf.readEoln();
    while (k--) {
        inf.readInt(1, n);
        inf.readSpace();
        inf.readInt(1, m);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
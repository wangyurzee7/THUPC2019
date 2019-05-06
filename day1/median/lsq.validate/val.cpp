#include "testlib.h"

static const int MAX_M = 10000;
static const int MAX_N = 500;
static const int MAX_A = 1e9;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    int m = inf.readInt(1, MAX_M, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int n = inf.readInt(1, MAX_N, "n_i");
        for (int j = 0; j < n; j++) {
            inf.readSpace();
            inf.readInt(0, MAX_A, "a_i,j");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

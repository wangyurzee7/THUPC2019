#include "testlib.h"
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>

static int C = 0;

static const int CONSTRAINTS[11][4] = {
    // n, c, k, M
    // c == INT_MAX: c == n
    // k < 0: k == -k
    {1000, 1000, 30, 2500},
    {1, INT_MAX, 1, 1},
    {10, INT_MAX, 10, 100},
    {20, INT_MAX, 0, 100},
    {30, INT_MAX, 0, 100},
    {30, INT_MAX, 30, 500},
    {500, INT_MAX, 0, 1000},
    {500, 30, -30, 1000},
    {500, INT_MAX, -30, 1000},
    {1000, INT_MAX, 0, 2500},
    {1000, INT_MAX, -30, 2500}
};

void read_case()
{
    int n = inf.readInt(1, CONSTRAINTS[C][0], "n"); inf.readSpace();
    int c = inf.readInt(1, CONSTRAINTS[C][1], "c"); inf.readEoln();
    if (CONSTRAINTS[C][1] == INT_MAX)
        ensuref(c == n, "Constraint c == n is violated");
    int c0 = inf.readInt(1, CONSTRAINTS[C][3], "C0"); inf.readSpace();
    int c1 = inf.readInt(1, CONSTRAINTS[C][3], "C1"); inf.readSpace();
    int d0 = inf.readInt(1, CONSTRAINTS[C][3], "D0"); inf.readSpace();
    int d1 = inf.readInt(1, CONSTRAINTS[C][3], "D1"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        int bi = inf.readInt(1, c, "b_i"); inf.readSpace();
        int si = inf.readInt(1, std::min(CONSTRAINTS[C][3], 10), "s_i");
        inf.readEoln();
    }
    int k = inf.readInt(
        CONSTRAINTS[C][2] < 0 ? -CONSTRAINTS[C][2] : 0,
        std::abs(CONSTRAINTS[C][2]), "k");
    inf.readEoln();
    std::set<int> ids;
    for (int i = 0; i < k; ++i) {
        int id = inf.readInt(1, n, "school idx"); inf.readSpace();
        int pf = inf.readInt(0, 3, "perference"); inf.readEoln();
        ensuref(ids.count(id) == 0, "Duplicate school indices");
        ids.insert(id);
    }
}

int main(int argc, char *argv[])
{
    registerValidation();
    if (argc >= 2) ::C = strtol(argv[1], NULL, 10);

    int T = inf.readInt(1, 5, "T"); inf.readEoln();
    for (int i = 1; i <= T; ++i) {
        fprintf(stderr, "Case #%d\n", i);
        read_case();
    }

    inf.readEof();
    return 0;
}

#include "../../../../testlib/testlib.h"
#include "../parse.hpp"

using namespace std;

#define USAGE_MSG "./val.exe -T -maxn -maxab -minp -maxp -maxx -maxst"

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);
    map<string, char*> args = parseArgs(argc, argv);

    CHECK_OR_EXIT(args.find("T") != args.end());
    CHECK_OR_EXIT(args.find("maxn") != args.end());
    CHECK_OR_EXIT(args.find("maxab") != args.end());
    CHECK_OR_EXIT(args.find("minp") != args.end());
    CHECK_OR_EXIT(args.find("maxp") != args.end());
    CHECK_OR_EXIT(args.find("maxx") != args.end());
    CHECK_OR_EXIT(args.find("maxst") != args.end());

    const int T = atoi(args["T"]);
    const int maxn = atoi(args["maxn"]);
    const int maxab = atoi(args["maxab"]);
    const double minp = atof(args["minp"]);
    const double maxp = atof(args["maxp"]);
    const int maxx = atoi(args["maxx"]);
    const int maxst = atoi(args["maxst"]);

    int kase = inf.readInt(1, T); inf.readEoln();
    while(kase --)
    {
        int n = inf.readInt(1, maxn); inf.readSpace();
        inf.readInt(0, maxab); inf.readSpace();
        inf.readInt(0, maxab); inf.readEoln();
        double p = inf.readDouble(minp, maxp); inf.readEoln();

        for(int i = 1; i <= n; i ++)
        {
            inf.readInt(1, maxx); inf.readSpace();
            inf.readInt(1, maxst); inf.readSpace();
            inf.readInt(1, maxst); inf.readEoln();
        }
    }

    inf.readEof();

    return 0;
}
//You can include .h file like testlib.h here
#include <cstdio>
#include <cstdlib>
#include <cstring>

FILE *inFile;
FILE *outFile;
FILE *ansFile;
FILE *scoreFile;
FILE *infoFile;
double score;
bool swap_flag;

const double eps = 1e-6;

#include <cmath>

void ret(double result, const char* info){
	if(swap_flag)
		fprintf(infoFile, "%s\n", info);	//Arbiter only allow to read EXACTLY one line info, no less and no more, and must BEFORE score
	fprintf(scoreFile, "%.6f\n", result * score);
	if(!swap_flag)
		fprintf(infoFile, "%s\n", info);
	exit(0);
}

int main(int argc, char **argv){
	//You'd better not change this swith block
	switch(argc){
		case 4:		//Arbiter
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			scoreFile = infoFile = fopen("/tmp/_eval.score", "w");
			score = 10;
			swap_flag = true;
			break;
		case 5:
			if(strcmp(argv[4], "THUOJ") == 0){	//Tsinghua OJ(OJ for DSA course)
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[3], "r");
				ansFile = fopen(argv[2], "r");
				scoreFile = stdout;
				infoFile = stdout;
				score = 100;
			}else{								//Tsinsen OJ
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[2], "r");
				ansFile = fopen(argv[3], "r");
				scoreFile = fopen(argv[4], "w");
				infoFile = fopen("tmp", "w");		//Tsinsen doesn't use this file
				score = 1;
			}
			break;
		case 7:		//Lemon and TUOJ
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			FILE *fs = fopen(argv[4], "r");
			if(fs)
				fscanf(fs, "%lf", &score);		//Current TUOJ
			else
				sscanf(argv[4], "%lf", &score);	//Lemon and future TUOJ
			scoreFile = fopen(argv[5], "w");
			infoFile = fopen(argv[6], "w");
			break;
	}
    int n;
    fscanf(inFile, "%d", &n);
    for (int i = 0; i < n; i++) {
        double ans, out;
        fscanf(ansFile, "%lf", &ans);
        if (fscanf(outFile, "%lf", &out) != 1)
            ret(0, "Cannot read answer");
        if (fabs(ans - out) > eps && fabs(ans - out) > eps * fabs(ans))
            ret(0, "Wrong answer");
    }
    ret(1, "Accepted");
	return 0;
}

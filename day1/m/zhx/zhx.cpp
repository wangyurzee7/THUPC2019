#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

int y,d=4;

int main()
{
	scanf("%d",&y);
	int x=1913;
	while (x<y)
	{
		x++;
		if (x%4!=0) d=(d+6)%7;
		else d=(d+5)%7;
		if (d==0) d+=7;
	}
	printf("%d\n",d+7);



	return 0;
}

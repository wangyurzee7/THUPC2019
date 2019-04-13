#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>

using namespace std;

int n;

queue<int> que;

stack<int> sta;

priority_queue<int> great;
priority_queue<int, vector<int>, greater<int> > small;


int main()
{
	scanf("%d",&n);

	int size = 0;
	bool able1=true,able2=true,able3=true,able4=true;
	for (int a=1;a<=n;a++)
	{
		int v,opt;
		scanf("%d%d",&opt,&v);
		if (opt==1)
		{
			size += 1;
			que.push(v);
			sta.push(v);
			great.push(v);
			small.push(v);
		}
		if (opt==2)
		{
			if (size && able1)
			{
				int vx=que.front();
				que.pop();
				if (vx!=v) able1=false;
			}
			else able1=false;
			if (size && able2)
			{
				int vx=sta.top();
				sta.pop();
				if (vx!=v) able2=false;
			}
			else able2=false;
			if (size && able3)
			{
				int vx=great.top();
				great.pop();
				if (vx!=v) able3=false;
			}
			else able3=false;
			if (size && able4)
			{
				int vx=small.top();
				small.pop();
				if (vx!=v) able4=false;
			}
			else able4=false;
			size--;
		}
	}
	if (able1) printf("Yes\n");
	else printf("No\n");
	if (able2) printf("Yes\n");
	else printf("No\n");
	if (able3) printf("Yes\n");
	else printf("No\n");
	if (able4) printf("Yes\n");
	else printf("No\n");

	return 0;
}

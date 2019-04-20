#include<cstdio>
int n;
int ans[100];
int main()
{
    int i;
    ans[0]=1;
    ans[1]=1;
    ans[2]=2;
    ans[3]=4;
    for(i=4;i<=64;++i)
        ans[i]=ans[i-1]+i-1+(i-1)*(i-2)*(i-3)/6;
    while(scanf("%d",&i)!=-1)
        printf("%d\n",ans[i]);
    return 0;
}
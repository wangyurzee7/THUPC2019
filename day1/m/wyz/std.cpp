#include <bits/stdc++.h>

using namespace std;

int main(){
    int y;
    scanf("%d",&y);
    int ans=12;
    for (int i=2019;i>y;--i){
        ++ans; // ans+=365%7;
        if ((i%4==0&&i%100!=0)||i%400==0)
            ++ans;
        if (ans>14) ans-=7;
    }
    printf("%d\n",ans);
    return 0;
}

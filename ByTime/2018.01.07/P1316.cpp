#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int n,m;
int a[100002];

bool check(int x)
{
    int j,cnt=0;
    for(int i=1;i<=n;)
    {
        for(j=i;j<=n && a[j+1]-a[i]<x;j++);
        i=j+1;
        cnt++;
    }
    return cnt>=m;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int l=0,r=a[n]-a[1]+10,mid;
    while (l+1<r)
    {
        mid=(l+r)>>1;
        if(check(mid))
            l=mid;
        else
            r=mid;
    }
    printf("%d\n",l);
    return 0;
}

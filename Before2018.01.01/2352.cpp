#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXN = 300009;

int a[MAXN],f[MAXN];
int n,k;

bool check(int v)
{
    int pos=0;
    for (int i=k;i<=n;i++)
	{
        if (a[i]-a[f[i-k]+1]<=v) pos=i;
        f[i]=pos;
    }
    return f[n]==n;
}

int main()
{
	freopen("2352.in","r",stdin);
	freopen("2352.out","w",stdout);
	scanf("%d%d",&n,&k);
    for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int l=-1,r=1000000009,mid;
    while (l+1<r)
	{
        mid=(l+r)>>1;
        if (check(mid)) r=mid;
        	else l=mid;
    }
    printf("%d\n",r);
    return 0;
}

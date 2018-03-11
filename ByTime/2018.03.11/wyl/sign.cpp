#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 300009,
		  INF  = MAXN;

struct Task {int x,y,i;};

Task a[300009];
int v[300009];
int n,m;
long long ans=0;
int miny;

int main()
{
	freopen("sign.in","r",stdin);
	freopen("sign.out","w",stdout);
	miny=INF;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]);
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].i=i;
		miny=min(a[i].y,miny);
	}
//	if (miny>=900 || (n<=2000 && m<=2000))
	{
		for (int i=1;i<=m;i++)
		{
			ans=0;
			for (int j=a[i].x;j<=n;j+=a[i].y)
				ans+=(long long)v[j];
			printf("%d\n",ans);
		}
	} 
	return 0;
}
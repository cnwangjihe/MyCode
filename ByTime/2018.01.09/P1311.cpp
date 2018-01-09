#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

const int MAXN = 8000009,
		  MAXK = 809;

struct Tdata
{
	int x;
	int y;
} a[MAXN];

int n,m,k,p;
bool f[MAXN];
long long ans1,ans2;
int c[MAXN],x[MAXK],d[MAXK];

int main()
{
	scanf("%d%d%d",&n,&k,&p);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		x[a[i].x]++;
		if(a[i].y>p)
			f[i]=0;
		else 
			f[i]=true;
		if(a[i].y<=p)
			c[(m++)+1]=i;
	}
	for(int i=0;i<52;i++)
	  ans1=ans1*2+x[i]*(x[i]-1),
	  ans1/=2;
	c[0]=1; c[(m++)+1]=++n;
	n--;
	for(int i=0;i<m;i++)
	{
		int l=c[i],r=c[i+1];
		if (a[c[i]].x>p) continue;
		if (l==r) continue;
		memset(d,0,sizeof d);
		for (int j=l+1;j<=r-1;j++)
			d[a[j].x]++;
		for (int j=0;j<52;j++)
			ans2=ans2+(d[j]*(d[j]-1)/2);
	}
	printf("%lld\n",(ans1*2-ans2*2)>>1);
	return 0;
}

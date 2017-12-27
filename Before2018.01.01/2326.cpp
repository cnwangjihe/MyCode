#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1000009;

int a[MAXN],b[MAXN],f[MAXN];
char c[MAXN];
int cnt=0,n;

void solve1()
{
	int p1=a[b[0]],p2=a[n]-a[b[0]],l=1,r=n;
	while (c[l]=='.') l++;
	while (c[r]=='.') r--;
	if (p1!=p2)
		printf("%d %d\n",max(p1,p2),(p1>p2?b[0]-l:r-b[0]));
	else
		printf("%d %d\n",p1,min(b[0]-l,r-b[0]));
	return ;
}



bool none(int l,int r)
{
	return r<l || a[r]-a[l-1]==0;
}

bool _check(int len)
{
	memset(f,0,sizeof f);
	for (int i=0;i<cnt;i++)
	{
		if(none(f[i]+1,b[i]-len-1 )) 
			f[i+1]=max(f[i+1],b[i]);
		if(none(f[i]+1,b[i]-1)) 
			f[i+1]=max(f[i+1],b[i]+len);
		if (i>0 && none(f[i-1]+1,b[i]-len-1) && b[i]-len<b[i-1]) 
			f[i+1]=max(f[i+1],b[i-1]+len);
	}
	return none(f[cnt]+1,n);
}

void solve2()
{
	int l=0,r=n,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (_check(mid)) r=mid;
			else l=mid;
	}
	printf("%d %d\n",a[n],r);
	return ;
}

int main()
{
//	freopen("2326.in","r",stdin);
//	freopen("2326.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		do {c[i]=getchar();}
			while (c[i]!='*' && c[i]!='.' && c[i]!='P');
		a[i]=a[i-1];
		if (c[i]=='*') a[i]++;
		if (c[i]=='P') b[cnt++]=i;
	}
	if (cnt==1) solve1();
		else solve2();
	return 0;
}

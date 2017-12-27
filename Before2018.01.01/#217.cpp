#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <cmath>

using namespace std;

struct Tnode
{
	int l,r;
};

const int MAXN = 4006;

bool f[MAXN][MAXN];
Tnode a[MAXN];
int ans=0,cnt=0,n;

bool _init(int l,int r,bool k)
{
	bool tmp=0,t;
	int mid=l;
	scanf("%d",&t);
	if (!k && t)
	{
		printf("OwO\n");
		exit(0);
	}
	f[l][r]=t;
	if (l==r)
	{
		if (t) 
			a[cnt].l=l,a[cnt].r=r,cnt++;
		return t;
	}
	scanf("%d",&mid);
	cerr << l << ' ' << mid << ' ' << r << '\n';
	tmp|=_init(l,mid,k&t);
	tmp|=_init(mid+1,r,k&t);
	if (!tmp && t)
	{
		a[cnt].l=l;
		a[cnt].r=r;
		cnt++;
	}
	return t;
}

int main()
{
	scanf("%d",&n);
	_init(1,n,1);
	for (int i=0;i<cnt;i++) cerr << '#' << a[i].l << ' ' << a[i].r << '\n';
	for (int i=1;i<cnt;i++)
		if ((a[i].l!=a[i-1].r+1) || 
			(f[a[i-1].l][a[i].r]) )
				ans++;
	cerr << cnt << endl;
	printf("%d\n",ans+1);
	
	return 0;
}

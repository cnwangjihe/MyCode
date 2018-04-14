#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 50009;

int t[MAXN*4];

int _ask(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u];
	int mid=(l+r)/2,ans=0;
	if (al<=mid)
		ans+=_ask(u*2,l,mid,al,ar);
	if (ar>mid)
		ans+=_ask(u*2+1,mid+1,r,al,ar);
	return ans;
}

void _update(int u,int l,int r,int p,int v)
{
	if (l==r)
	{
		t[u]+=v;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_update(u*2,l,mid,p,v);
	else
		_update(u*2+1,mid+1,r,p,v);
	t[u]=t[u*2]+t[u*2+1];
	return ;
}
void _upd(int u,int l,int r,int p,int v)
{
	if (l==r)
	{
		t[u]=v;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		_upd(u*2,l,mid,p,v);
	else
		_upd(u*2+1,mid+1,r,p,v);
	t[u]=t[u*2]+t[u*2+1];
	return ;
}

int main()
{
	int ttt;
	int n,a,b;
	char c[100];
	scanf("%d",&ttt);
	for (int tt=1;tt<=ttt;tt++)
	{
		printf("Case %d:\n",tt);
		scanf("%d",&n);
		memset(t,0,sizeof t);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			_upd(1,1,n,i,a);
		}
		do
		{
			scanf("%s",c);
			if (c[0]=='Q')
			{
				scanf("%d%d",&a,&b);
				printf("%d\n",_ask(1,1,n,a,b));
			}
			if (c[0]=='A')
			{
				scanf("%d%d",&a,&b);
				_update(1,1,n,a,b);
			}
			if (c[0]=='S')
			{
				scanf("%d%d",&a,&b);
				_update(1,1,n,a,-b);
			}
			if (c[0]=='E')
				break;
		}
		while (1);
	}
}
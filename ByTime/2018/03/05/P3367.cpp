#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <stdio.h>

using namespace std;

int fa[10006];
int x,y,k,n,m,fx,fy;

int _find(int u)
{
	int x=u,t;
	while (fa[u]!=u)
		u=fa[u];
	while (fa[x]!=x)
	{
		t=fa[x];
		fa[x]=u;
		x=t;
	}
	return u;
}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&k,&x,&y);
		fx=_find(x);fy=_find(y);
		if (k-1)
			printf("%c\n",fx==fy?'Y':'N');
		else
		{
			if (fx!=fy) fa[fx]=fy;
		}
	}
	return 0;
}

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <stdio.h>

using namespace std;

struct Tedge {int x,y,z;};

const int MAXN = 309,
		  MAXM = MAXN*MAXN;

Tedge e[MAXM];
int n,m,ans;
int fa[MAXN];


bool _cmp(Tedge a,Tedge b) {return a.z<b.z;}

int _find(int u)
{
	int x=u,t;
	while (x!=fa[x]) x=fa[x];
	while (u!=fa[u])
	{
		t=fa[u];
		fa[u]=x;
		u=t;
	}
	return u;
}

int main()
{
	int fx,fy;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=0;i<m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
	sort(e,e+m,_cmp);
	for (int i=0;i<m;i++)
	{
		fx=_find(e[i].x),fy=_find(e[i].y);
		if (fx==fy) continue;
		fa[fx]=fy;
		ans=e[i].z;
	}
	printf("%d %d\n",n-1,ans);
	return 0;
}
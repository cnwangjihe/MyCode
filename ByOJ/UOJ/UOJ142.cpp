#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1000000009,
		  MAXNM= 4000009;

int n,m,k,p;
int fa[MAXNM];
bool ban[MAXNM],vis[MAXNM];
bool flag;

int _getfp(int x,int y) {return x*m+y;}

void reset(int size)
{
	for (int i=0;i<size;i++)
		fa[i]=i,ban[i]=0,vis[i]=0;
	p=0;
	flag=1;
	return ;
}

int _find(int u)
{
	int x=u,tmp;
	while (u!=fa[u]) u=fa[u];
	while (x!=fa[x])
	{
		tmp=fa[x];
		fa[x]=u;
		x=tmp;
	}
	return u;
}

bool _connect(int x,int y)
{
	if (ban[x] || ban[y]) return 1;
	int fx=_find(x),fy=_find(y);
	if (fx==fy) return 0;
	fa[fx]=fy;
	return 1;
}

int _getblock(int size)
{
	int cnt=0;
	for (int i=0;i<size;i++)
		cnt+=_find(i)==i;
	//	if (_find(i)==i) cerr << i << ' ' ;
	return cnt;
}

int main()
{
	int ttt,x,y;
	scanf("%d",&ttt);
	for (;ttt;ttt--)
	{
		scanf("%d%d%d",&n,&m,&k);
		if (n>400000 || m>400000 || n*m>400000) 
		{
			printf("No\n");
			for (int i=0;i<k;i++)
				scanf("%d%d",&x,&y);
			continue;
		}
		reset(n*m);
		for (int i=0;i<k;i++)
			scanf("%d%d",&x,&y),
			ban[_getfp(x-1,y-1)]=1;
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<m;j++)
			{
				if (i!=0) flag&=_connect(_getfp(i,j),_getfp(i-1,j));
				if (j!=0) flag&=_connect(_getfp(i,j),_getfp(i,j-1));
					else flag&=_connect(_getfp(i,j),_getfp(i,m-1));
			}
		}
	//	cerr << _getblock(n*m) << '\n';
		if (_getblock(n*m)==k+1 && flag) printf("Yes\n");
			else printf("No\n");
	}
	return 0;
}

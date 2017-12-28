#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 200009;

struct Tedge
{
	int a,b,v;
}edge[MAXN];

int fa[MAXN];
bool f[MAXN];
int n,m,ans=0;

bool _cmp(Tedge a,Tedge b) {return a.v>b.v;}

int u_f(int root)
{
	int x=root,tmp;
	while (x!=fa[x]) x=fa[x];
	while (root!=fa[root])
	{
		tmp=fa[root];
		fa[root]=x;
		root=tmp;
	}
	return root;
}

int main()
{
	freopen("2343.in","r",stdin);
	freopen("2343.out","w",stdout);
	memset(f,0,sizeof f);
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++) fa[i]=i;
	for (int i=0;i<m;i++)
		scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].v);
	sort(edge,edge+m,_cmp);
	for(int i=0;i<m;i++)
	{
		int x=u_f(edge[i].a),y=u_f(edge[i].b);
		if(x!=y)
		{
			if(f[x] && f[y]) continue;
			f[x]=f[x]|f[y];
			fa[y]=x;
			ans+=edge[i].v;
		}
		else 
			if(!f[x]) ans+=edge[i].v,f[x]=1;
	}
	printf("%d\n",ans);
	return 0;
}

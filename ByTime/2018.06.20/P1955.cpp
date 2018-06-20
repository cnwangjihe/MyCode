#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200019;

map<int,int> val;

int ans,cnt,n;
int u[MAXN],v[MAXN],t[MAXN];
int fa[MAXN];

int _find(int u)
{
	int x=u,tmp;
	while (x!=fa[x])
		x=fa[x];
	while (u!=fa[u])
	{
		tmp=fa[u];
		fa[u]=x;
		u=tmp;
	}
	return u;
}

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		int fu,fv;
		val.clear();
		cnt=ans=1;
		scanf("%d",&n);
		for (int i=0;i<=2*n;i++)
			fa[i]=i;
		for (int i=0;i<n;i++)
		{
			scanf("%d%d%d",&u[i],&v[i],&t[i]);
			if (!val.count(u[i]))
				val[u[i]]=cnt++;
			if (!val.count(v[i]))
				val[v[i]]=cnt++;
			u[i]=val[u[i]];
			v[i]=val[v[i]];
		}
		for (int i=0;i<n;i++)
		{
			if (!t[i])
				continue;
			fu=_find(u[i]),fv=_find(v[i]);
			if (fu!=fv)
				fa[fu]=fv;
		}
		for (int i=0;i<n;i++)
		{
			if (t[i])
				continue;
			fu=_find(u[i]),fv=_find(v[i]);
			if (fu==fv)
			{
				ans=0;
				break;
			}
		}
		printf("%s\n",ans?"YES":"NO");
	}
	return 0;
}
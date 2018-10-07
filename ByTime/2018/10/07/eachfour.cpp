#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400009;

int n,m,q,ans=-1;
int fa[MAXN];

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
	freopen("eachfour.in","r",stdin);
	freopen("eachfour.out","w",stdout);
	int a,b;
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n+m;i++)
		fa[i]=i;
	for (int i=1;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		b+=n;
		fa[_find(a)]=_find(b);
	}
	for (int i=1;i<=n+m;i++)
		if (_find(i)==i)
			ans++;
	printf("%d\n",ans);
	return 0;
}
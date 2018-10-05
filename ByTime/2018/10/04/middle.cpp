#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tnode {int v,s,lc,rc;};
struct Tquery{int v,i;};

Tnode t[MAXN];
Tquery q[MAXN];
int ans[MAXN],v[MAXN];
int n,m,fp=0;

void _insert(int &u,int v)
{
	if (u==0)
	{
		u=++fp;
		t[u].v=v;
		t[u].s=1;
		return ;
	}
	if (v<=t[u].v)
		_insert(t[u].lc,v);
	else
		_insert(t[u].rc,v);
	t[u].s=t[t[u].lc].s+t[t[u].rc].s+1;
	return ;
}

int _query(int u,int p)
{
	if (!u)
		return 0;
	if (p==t[t[u].lc].s+1)
		return t[u].v;
	if (p<=t[t[u].lc].s)
		return _query(t[u].lc,p);
	else
		return _query(t[u].rc,p-t[t[u].lc].s-1);
}

bool _cmp(Tquery a,Tquery b) {return a.v<b.v;}

int main()
{
	freopen("middle.in","r",stdin);
	freopen("middle.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]);
	for (int i=0;i<m;i++)
		scanf("%d",&q[i].v),q[i].i=i;
	sort(q,q+m,_cmp);
	int rt=0,j=0,tmp;
	for (int i=1;i<=n;i++)
	{
		_insert(rt,v[i]);
		if (q[j].v!=i)
			continue;
		tmp=_query(rt,i/2+1);
		while (q[j].v==i)
			ans[q[j++].i]=tmp;
	}
	for (int i=0;i<m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
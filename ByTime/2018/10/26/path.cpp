#include <bits/stdc++.h>

using namespace std;

const int MAXN = 600009;

struct Tedge {int a,b,v;};

Tedge e[MAXN];
int f[MAXN],g[MAXN];
int n,m,t=0,ans=0;

bool _cmp(Tedge a,Tedge b) {return a.v<b.v;}

int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].v);
	sort(e+1,e+1+m,_cmp);
	for (int i=1;i<=m;i++)
	{
		for (;e[t+1].v!=e[i].v;)
		{
			t++;
			g[e[t].b]=max(g[e[t].b],f[t]);
		}
		f[i]=g[e[i].a]+1;
		ans=max(ans,f[i]); 
	}
	printf("%d\n",ans);
	return 0;
}

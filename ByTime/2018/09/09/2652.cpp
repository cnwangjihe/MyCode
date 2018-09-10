#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;
const long long INF = 1000009ll*1000009ll;

struct Tnode{long long x,y;};
struct Tline{long long v;int i,j;};

Tline line[501*501];
Tnode a[MAXN],best[MAXN];
long long cost,ans;
bool vis[1001];
int fa[509];
int n,m;
bool type;

bool _cmp(Tnode a,Tnode b) {return a.x==b.x?a.y<b.y:a.x<b.x;}
bool _cmp2(Tline a,Tline b) {return a.v<b.v;}

int find(int u)
{
	int x=u,t;
	while (u!=fa[u])
		u=fa[u];
	while (x!=fa[x])
	{
		t=fa[x];
		fa[x]=u;
		x=t;
	}
	return u;
}

int main()
{
	freopen("2652.in","r",stdin);
	freopen("2652.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		type=0;
		m=0;
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
		{
			scanf("%lld%lld",&a[i].x,&a[i].y);
			if (a[i].x>1000 || a[i].y>1000)
				type=1;
		}
		sort(a+1,a+n+1,_cmp);
		if (!type)
		{
			memset(vis,0,sizeof vis);
			m=0;
			best[++m]=a[1];
			vis[a[1].y]=1;
			for (int i=2;i<=n;i++)
			{
				cost=INF;
				for (int j=1;j<=m;j++)
					cost=min(cost,a[i].x*best[j].x+a[i].y*best[j].y);
				ans+=cost;
				if (!vis[a[i].y])
				{
					best[++m]=a[i];
					vis[a[i].y]=1;
				}
			}
			printf("%lld\n",ans);
			continue;
		}
		for (int i=1;i<=n;i++)
			fa[i]=i;
		for (int i=1;i<=n;i++)
			for (int j=1;j<i;j++)
			{
				line[m].i=i;
				line[m].j=j;
				line[m++].v=a[i].x*a[j].x+a[i].y*a[j].y;
			}
		sort(line,line+m,_cmp2);
		int fx,fy;
		for (int i=0;i<m;i++)
		{
			fx=find(line[i].i),fy=find(line[i].j);
			if (fx!=fy)
			{
				ans+=line[i].v;
				fa[fx]=fy;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
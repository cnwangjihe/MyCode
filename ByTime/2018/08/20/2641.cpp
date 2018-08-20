#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50009;

int fa[MAXN],col[MAXN],inc[MAXN];
int n,k,ans=0;

int find(int u)
{
	if (fa[u]==u)
		return u;
	int x=find(fa[u]);
	(inc[u]+=inc[fa[u]])%=3;
	(col[u]+=inc[fa[u]])%=3;
	return fa[u]=x;
}

void merge(int x,int y,int val)
{
	fa[y]=x;
	(inc[y]+=val)%=3;
	(col[y]+=val)%=3;
	return ;
}

int main()
{
	freopen("2641.in","r",stdin);
	freopen("2641.out","w",stdout);
	int x,y,t,fx,fy;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=0;i<k;i++)
	{
		scanf("%d%d%d",&t,&x,&y);
		if (x>n || y>n)
		{
			ans++;
			continue;
		}
		fx=find(x),fy=find(y);
		if (fx==fy)
			ans+=((col[x]+t-1)%3!=col[y]);
		else
			merge(fx,fy,(col[x]-col[y]+(t-1)+3)%3);
	}
	printf("%d\n",ans);
	return 0;
}
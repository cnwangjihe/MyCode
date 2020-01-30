// Date      : 2019-04-16 11:41:40
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

#define mkp make_pair

const int MAXN = 1009;

pair<int,pair<int,int> > t[MAXN*MAXN];
int a[MAXN];
int fa[MAXN];
int n,fp=0;
long long ans=0;

int Find(int u)
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
	freopen("2865.in","r",stdin);
	freopen("2865.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]^=a[i-1];
	}
	for (int i=1;i<=n;i++)
		fa[i]=i;
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++)
			t[fp++]=mkp(a[j]^a[i-1],mkp(i-1,j));
	sort(t,t+fp);
	for (int i=0;i<fp;i++)
	{
		int fx=Find(t[i].second.first),fy=Find(t[i].second.second);
		if (fx==fy)
			continue;
		ans+=t[i].first;
		fa[fx]=fy;
	}
	printf("%lld\n",ans);
	return 0;
}
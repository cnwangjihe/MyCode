#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 20009,
		  MAXM = 100009;

struct UFset
{
	int fa[MAXN];
	void Reset() {for (int i=0;i<MAXN;i++) fa[i]=i;}
	UFset() {Reset();}
	int Find(int u) {return fa[u]==u?u:fa[u]=Find(fa[u]);}
	bool Check(int u,int v) {return Find(u)==Find(v);}
	void Union(int u,int v) {fa[Find(u)]=Find(v);}
};
struct Edge {int a,b,t;};

UFset s1,s2;
Edge e[MAXM];
int cnt[2],k[2],ans[MAXN];
int n,m,tp=0;

int main()
{
	scanf("%d%d%d",&n,&m,&k[0]);
	k[1]=n-1-k[0];
	for (int i=0;i<m;i++)
		scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].t);
	for (int i=0;i<m;i++)
	{
		if (!e[i].t)
			continue;
		if (!s1.Check(e[i].a,e[i].b))
			s1.Union(e[i].a,e[i].b);
	}
	for (int i=0;i<m;i++)
	{
		if (e[i].t)
			continue;
		if (!s1.Check(e[i].a,e[i].b))
			s2.Union(e[i].a,e[i].b),s1.Union(e[i].a,e[i].b),ans[tp++]=i,cnt[e[i].t]++;
	}
	s1.Reset();
	for (int i=0;i<m;i++)
	{
		if (e[i].t)
			continue;
		if (!s1.Check(e[i].a,e[i].b))
			s1.Union(e[i].a,e[i].b);
	}
	for (int i=0;i<m;i++)
	{
		if (!e[i].t)
			continue;
		if (!s1.Check(e[i].a,e[i].b))
			s2.Union(e[i].a,e[i].b),s1.Union(e[i].a,e[i].b),ans[tp++]=i,cnt[e[i].t]++;
	}
	for (int i=0;i<m;i++)
	{
		if (s2.Check(e[i].a,e[i].b) || cnt[e[i].t]>=k[e[i].t])
			continue;
		cnt[e[i].t]++;
		ans[tp++]=i;
		s2.Union(e[i].a,e[i].b);
	}
	if (tp!=n-1 || cnt[0]!=k[0] || cnt[1]!=k[1])
		return printf("no solution\n")&0;
	for (int i=0;i<tp;i++)
		printf("%d %d %d\n",e[ans[i]].a,e[ans[i]].b,e[ans[i]].t);
	return 0;
}
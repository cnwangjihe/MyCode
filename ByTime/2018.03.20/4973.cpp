#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

const int MAXN=100009;

struct Telement {int u,v,w;};

int n,m;
int fa[MAXN],mx[MAXN],mn[MAXN];
long long ret;
long long ans[MAXN];
 
Telement e[MAXN*2],cit[MAXN];
 
bool cmp(Telement A,Telement B) {return A.w<B.w;}
int findf(int x) {return fa[x]==x?x:fa[x]=findf(fa[x]);}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&cit[i].u,&cit[i].v);
		fa[i]=i;mx[i]=cit[i].u;mn[i]=cit[i].v;
		ans[i]=1ll*mx[i]*mn[i];
	}
	for(int i=1;i<=m;++i)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
		int fu=findf(e[i].u),fv=findf(e[i].v);
		if(fu==fv)
			continue;
		fa[fu]=fv;
		ans[fv]=min(ans[fu]+ans[fv],1ll*max(e[i].w,max(mx[fu],mx[fv]))*min(mn[fu],mn[fv]));
		mx[fv]=max(mx[fu],mx[fv]);mn[fv]=min(mn[fu],mn[fv]);
	}
	for(int i=1;i<=n;++i)
		if(fa[i]==i)
			ret+=ans[i];
	printf("%lld\n",ret);
	return 0;
}
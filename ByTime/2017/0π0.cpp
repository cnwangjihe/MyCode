#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 300008;

struct Tgrass
{
	int l,r,m;
}g[MAXN];

int n,t;

bool cmpl(Tgrass A,Tgrass B){return A.l<B.l;}

void solve()
{
	int minr,ans=1;
	sort(g+1,g+n+1,cmpl);
	minr=g[1].r;
	for(int i=1;i<=n;i++)
	{
	//	cerr << minr << " ** "; 
		if(minr<g[i].l) 
		{
			ans++;
			minr=g[i].r;
		}
		else minr=min(minr,g[i].r);
	}
	printf("%d\n",ans);
	return ;
}

int main()
{
//	freopen("grass.in","r",stdin);
//	freopen("grass.out","w",stdout);
	
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&g[i].l,&g[i].r);
		g[i].m=(g[i].l+g[i].r)/2;
	}
	solve();
	return 0;
}

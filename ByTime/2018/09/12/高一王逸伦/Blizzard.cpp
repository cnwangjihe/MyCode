#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tsq{int v,i;};

long long val,ans;
int n,m,k;
int used[MAXN];
Tsq x[MAXN],y[MAXN];

bool _cmp(Tsq a,Tsq b) {return a.v<b.v;}

int main()
{
	freopen("Blizzard.in","r",stdin);
	freopen("Blizzard.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		memset(used,0,sizeof used);
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&x[i].v,&y[i].v);
			x[i].i=y[i].i=i;
		}
		sort(x+1,x+1+n,_cmp);
		sort(y+1,y+1+n,_cmp);
		int j=min(m+1,n);
		k=0;
		for (int i=1;i<j;i++)
			used[y[i].i]++,k++;
		for (int i=1;i<=n;i++)
		{
			while (i<=n && used[x[i].i])
				used[x[i++].i]++;
			val=1ll*x[i].v*y[j].v;
			if (!used[x[i].i])
				k++;
			used[x[i].i]++;
		//	cerr << i << ' ' << j << endl;
			ans=max(ans,val);
			if (k>m)
			{
				while (j && --used[y[--j].i]!=0);
				k--;
			}
			if (!j)
				break;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
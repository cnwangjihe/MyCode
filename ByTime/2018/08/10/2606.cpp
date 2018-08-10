#include <bits/stdc++.h>

using namespace std;

const int MAXN = 509;

struct Tline {int a,b;};

Tline a[MAXN];
int ans,n,L,R;
int f[MAXN][MAXN];
bool vis[MAXN][MAXN];

bool _cmp(Tline a,Tline b) {return (a.a==b.a)?(a.b<b.b):(a.a<b.a);}

int main()
{
	freopen("2606.in","r",stdin);
	freopen("2606.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		memset(vis,0,sizeof vis);
		memset(f,0,sizeof f);
		scanf("%d%d%d",&n,&L,&R);
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i].a);
			a[i].b=a[i].a+R;
		}
		ans=n;
		sort(a,a+n,_cmp);
		for (int i=0;i<n;i++)
		{
			if (a[i].a<0 || a[i].b>L)
				continue;
			vis[1][i]=1;
			f[1][i]=a[i].a/R;
		}
		for (int i=2;i<=n;i++)
			for (int j=0;j<n;j++)
			{
				if (a[j].a<0 || a[j].b>L)
					continue;
				for (int k=j+1;k<n;k++)
				{
					if (a[k].a<0 || a[k].b>L)
						continue;
					if (a[k].a<a[j].b)
						continue;
					if (!vis[i-1][j])
						continue;
					f[i][k]=max(f[i][k],f[i-1][j]+(a[k].a-a[j].b)/R);
					vis[i][k]=1;
				}
			}
		int tmp;
		for (int i=1;i<=n;i++)
			for (int j=0;j<n;j++)
			{
				if (!vis[i][j])
					continue;
				tmp=f[i][j]+(L-a[j].b)/R;
				if  (tmp+i>=n)
					ans=min(ans,n-i);
			}
		printf("%d\n",ans);
	}
	return 0;
}

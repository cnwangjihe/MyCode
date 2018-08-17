#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int cnt,p;
int a[MAXN],f[1<<(MAXN)];
int st,n;

int main()
{
	freopen("2634.in","r",stdin);
	freopen("2634.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		cnt=0;
		memset(f,0x3f,sizeof f);
		scanf("%d",&n);
		for (int i=0;i<n;i++)
			scanf("%d",&a[i]);
		sort(a,a+n);
		if (a[0]==a[1] && a[0]==1)
		{
			printf("-1\n");
			continue;
		}
		if (a[0]==1)
		{
			f[0]=1;
			for (int i=0;i<(1<<(n-1));i++)
				for (int j=1;j<n;j++)
				{
					if (i&(1<<(j-1)))
						continue;
					f[i|(1<<(j-1))] = min(f[i|(1<<(j-1))],f[i]+(f[i]+a[j]-2)/(a[j]-1));
				}
			printf("%d\n",f[(1<<(n-1))-1]);
			continue;
		}
		for (int j=0;j<n;++j)
			f[1<<j]=1;
		for (int i=1;i<(1<<n);i++)
			for (int j=0;j<n;j++)
			{
				if (i&(1<<j))
					continue;
				f[i|(1<<j)] = min(f[i|(1<<j)],f[i]+(f[i]+a[j]-2)/(a[j]-1));
			}
		printf("%d\n",f[(1<<n)-1]);
	}
	return 0;
}
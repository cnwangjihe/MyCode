#include <bits/stdc++.h>

using namespace std;

const int MAXN = 209,
		  INF  = 1009;

char s[MAXN];
int a[MAXN],c[MAXN];
int f[MAXN][MAXN];
int len,n;

int main()
{
	freopen("2584.in","r",stdin);
	freopen("2584.out","w",stdout);
	int ttt,r;
	scanf("%d",&ttt);
	for (int tt=1;tt<=ttt;tt++)
	{
		scanf("%s",s+1);
		len=strlen(s+1);
		n=0,memset(c,0,sizeof c);
		for (int i=1;i<=len;i++)
			if (s[i]!=s[i-1])
				a[++n]=s[i]-48,c[n]=1;
			else
				c[n]++;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (i==j)
					f[i][j]=(c[i]>=3?0:3-c[i]);
				else
					f[i][j]=(i>j?0:INF);
		for (int i=2;i<=n;i++)
		{
			for (int l=1;l+i-1<=n;l++)
			{
				r=l+i-1;
				for (int mid=l;mid<r;mid++)
				{
					f[l][r]=min(f[l][r],f[l][mid]+f[mid+1][r]);
					if (mid>l && a[l]==a[mid] && a[mid]==a[r] && c[mid]==1 && (c[l]==1 || c[r]==1))
						f[l][r]=min(f[l][r],f[l+1][mid-1]+f[mid+1][r-1]);
				}
				if (a[l]==a[r])
					f[l][r] = min(f[l][r],max(0,3-c[l]-c[r])+f[l+1][r-1]);

			}
		}
		printf("Case #%d: %d\n",tt,f[1][n]);
	}
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXK = 27;

int a[MAXN];
int cnt[MAXK],cnt2[MAXK];
int f[MAXN],f2[MAXN];
int n,k;

bool dfs(int len,int lim)
{
	if (len==n)
	{
		if (lim!=k-1)
			return 0;
		bool fg=1;
		int ti;
		for (int i=n-1;~i;i--)
		{
			f2[cnt2[a[i]]++]--;
			if (f2[cnt2[a[i]]]!=0)
			{
				ti=i;
				fg=0;
				break;
			}
			f2[cnt2[a[i]]]++;
		}
		if (fg)
		{
			for (int i=0;i<n;i++)
			{
				f2[cnt2[a[i]]]--;
				f2[--cnt2[a[i]]]++;
			}
		}
		else
		{
			f2[--cnt2[a[ti]]]++;
			for (int i=ti+1;i<n;i++)
			{
				f2[cnt2[a[i]]]--;
				f2[--cnt2[a[i]]]++;
			}
		}
		if (!fg)
			return 0;
		for (int i=0;i<n;i++)
			putchar(a[i]+'a');
		putchar('\n');
		return 1;
	}
	int t;
	for (int i=0;i<min(k,lim+2);i++)
	{
		if (f[cnt[i]+1]!=0)
			continue;
		f[cnt[i]]--;
		f[++cnt[i]]++;
		a[len]=i;
		t=dfs(len+1,max(i,lim));
		f[cnt[i]]--;
		f[--cnt[i]]++;
		if (t)
			return 1;
	}
	return 0;
}

int main()
{
	freopen("gre.in","r",stdin);
	freopen("gre.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d",&n,&k);
		if (n<=20 && k>=4)
		{
			printf("CiYe\n");
			continue;
		}
		f[0]=100;
		f2[0]=100;
		if (k==3 && n>40)
		{
			int m=n-40;
			n=40;
			cnt[0]=m;
			f[m]=1;
			for (int i=0;i<m;i++)
				putchar('a');
			if (!dfs(0,-1))
				printf("CiYe\n");
			f[m]=0;
			cnt[0]=0;
			n=40+m;
			continue;
		}
		if (!dfs(0,-1))
			printf("CiYe\n");
	}
	return 0;
}

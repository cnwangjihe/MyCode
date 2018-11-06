#include <bits/stdc++.h>

using namespace std;

const int MAXL = 2000009,
		  MAXN = 509,
		  MAXK = 64;

bitset<MAXN> g[MAXK][MAXN],f[MAXK][MAXN],t1[MAXN],t2[MAXN];
bitset<MAXN> c,tmp;

bool s[MAXL];
int n,m;
long long ans=0;

void calc(int v)
{
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) 
		{
		if (g[v-1][i][j]==1)
			t1[j][i]=1;
		else
			t1[j][i]=0;
		if (f[v-1][i][j]==1)
			t2[j][i]=1;
		else
			t2[j][i]=0;
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			tmp=g[v-1][i] & t2[j];
			g[v][i][j]=tmp.any();
			tmp=f[v-1][i] & t1[j];
			f[v][i][j]=tmp.any();
		}
	}
	return ;
}

int main()
{
	freopen("2704.in","r",stdin);
	freopen("2704.out","w",stdout);
	int x,y,z;
	s[0]=0;
	for (int i=0;i<20;i++)
		for (int j=0;j<(1<<i);j++)
			s[j+(1<<i)]=!s[j];
/*	for (int i=0;i<100;i++)
	{
		if (i%4==0 && i)
			putchar(' ');
		cerr << s[i];
	}*/
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if (z)
			f[0][x][y]=1;
		else
			g[0][x][y]=1;
	}
	for (int i=1;i<MAXK;i++)
		 calc(i);
	int t=1;
	c[1]=1;
	for (int i=MAXK-2;~i;i--)
	{
		tmp=0;
		for (int j=1;j<=n;j++)
			if (c[j])
			{
				if (t-1)
					tmp|=f[i][j];
				else
					tmp|=g[i][j];
			}
		if (tmp.any())
		{
			t=(t==2)?1:2;
			c=tmp;
			ans+=(1ll<<i);
		}
	}
	printf("%lld\n",ans>1000000000000000000ll?-1:ans);
	return 0;
}
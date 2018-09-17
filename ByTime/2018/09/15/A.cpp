#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;

struct Tnode{int v,i;};

Tnode a[MAXN][MAXN],b[MAXN][MAXN];
int xrank[MAXN][MAXN],yrank[MAXN][MAXN];
int ans[MAXN][MAXN];
int n,m,q;

inline int read()
{
	int x=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar());
	for (;c>='0'&&c<='9';c=getchar())
		x=x*10+(c^48);
	return x;
}

bool _cmp(Tnode a,Tnode b) {return a.v>b.v;}

int main()
{
	int x,y;
	n=read(),m=read(),q=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			a[i][j].v=b[j][i].v=read();
			a[i][j].i=j;
			b[j][i].i=i;
		}
	for (int i=1;i<=n;i++)
	{
		sort(a[i]+1,a[i]+1+m,_cmp);
		for (int j=1;j<=m;j++)
			xrank[i][a[i][j].i]=j;
	}
	for (int i=1;i<=m;i++)
	{
		sort(b[i]+1,b[i]+1+n,_cmp);
		for (int j=1;j<=n;j++)
			yrank[b[i][j].i][i]=j;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			ans[xrank[i][j]][yrank[i][j]]++;
	for (int i=0;i<q;i++)
	{
		x=read(),y=read();
		printf("%d\n",ans[x][y]);
	}
	return 0;
}

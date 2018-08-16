#include <bits/stdc++.h>

using namespace std;

const int MAXN = 509,
		  MAXK = 31;

int n,m,k,rk;
int t;
char s[MAXN],c[MAXN][MAXK],ans[MAXN];

int main()
{
	freopen("2625.in","r",stdin);
	freopen("2625.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&k,&rk);
	rk--;
	for (int i=0;i<n;i++)
		do {s[i]=getchar();}
			while (s[i]!='#' && (s[i]<'a' || s[i]>'z'));
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<k;j++)
			do {c[i][j]=getchar();}
				while (c[i][j]<'a' || c[i][j]>'z');
		sort(c[i],c[i]+k);
	}
	for (int i=m-1;~i;i--)
	{
		ans[i]=c[i][rk%k];
		rk/=k;
	}
	t=0;
	for (int i=0;i<n;i++)
		putchar(s[i]=='#'?ans[t++]:s[i]);
	putchar('\n');
	return 0;
}
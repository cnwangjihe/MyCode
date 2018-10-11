#include <bits/stdc++.h>

using namespace std;

int a,b,c,d;

void solve1()
{
	for (int i=min(b,d);i;i--)
		if ((a-1)/i!=b/i && (c-1)/i!=d/i)
		{
			printf("%d\n",i);
			break;
		}
}
/*
void calc(int k)
{
	int p1=0,p2=0,p=0,last=1;
	while (p1<n[k] || pp2<n[k+1])
	{
		if (g[k][p1+1]<g[k+1][p2+1])
		{
			p1++;
			if (last<=g[k][p1] && a/g[k][p1]!=b/g[k][p1])
				f[k][++p].l=last,f[k][p].r=g[k][p1];
			last=g[k][pp1]+1;
		}
		else
		{
			pp2++;
			if (last<=g[k+1][pp2] && a/g[k+1][pp2]!=b/g[k+1][pp2])
				f[k][++p].l=last,f[k][p].r=g[k+1][p2];
			last=g[k+1][pp2]+1;
		}
	}
}
*/

int main()
{
	freopen("gcd.in","r",stdin);
	freopen("gcd.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
	//	if (a<=1000 && b<=1000 && c<=1000 && d<=1000)
	//	{
			solve1();
	//		continue;
	//	}
		/*
		for (int i=1;i*i<=a;i++)
		{
			if (a%i==0)
				g[0][++n[0]]=i;
			if (b%i==0)
				g[1][++n[1]]=i;
			if (c%i==0)
				g[2][++n[2]]=i;
			if (d%i==0)
				g[3][++n[3]]=i;
		}
		*/
	}
	return 0;
}
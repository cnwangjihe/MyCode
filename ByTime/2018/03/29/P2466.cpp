#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1009,
		  INF  = 0x7fffffff;

struct Tnode {int x,y,v;};

Tnode ball[MAXN];
int f[MAXN][MAXN],g[MAXN][MAXN];
int sum[MAXN];
int n,x0,ans=0;

bool _cmp(Tnode a,Tnode b){return a.x<b.x;}
int calc(int l,int r) {return r>=l?sum[r]-sum[l-1]:0;}

int main()
{
	int t1,t2;
	memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	scanf("%d%d",&n,&x0);
	for (int i=1;i<=n;i++)
		scanf("%d",&ball[i].x),ball[i].x-=x0;
	for (int i=1;i<=n;i++)
		scanf("%d",&ball[i].y),ans+=ball[i].y;
	for (int i=1;i<=n;i++)
		scanf("%d",&ball[i].v);
	ball[++n].x=0;
	sort(ball+1,ball+n+1,_cmp);
	for (int i=1;i<=n;i++)
		if (!ball[i].v && !ball[i].x)
			f[i][i]=g[i][i]=0;
	sum[0]=0;
	for (int i=1;i<=n;i++)
		sum[i]=sum[i-1]+ball[i].v;
	for (int k=1;k<=n;k++)
	{
		for (int i=1,j=i+k;j<=n;i++,j++)
		{
			t1=calc(1,i)+calc(j+1,n);
			t2=calc(1,i-1)+calc(j,n);
			f[i][j]=min(f[i][j],f[i+1][j]+t1*(ball[i+1].x-ball[i].x));
			f[i][j]=min(f[i][j],g[i+1][j]+t1*(ball[j].x-ball[i].x));
			g[i][j]=min(g[i][j],f[i][j-1]+t2*(ball[j].x-ball[i].x));
			g[i][j]=min(g[i][j],g[i][j-1]+t2*(ball[j].x-ball[j-1].x));
		}
	}
	ans-=min(g[1][n],f[1][n]);
	printf("%.3f\n",(double)ans*1.0/1000);
	return 0;
} 
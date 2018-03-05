#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAXN = 1009,
		  MAXM = (1<<8)+2,
		  INF  = 0x7fffffff;

int f[MAXN][MAXM][20];
int a[MAXN],b[MAXN];
int ttt,last,n,ans;

int cost(int x,int y) {return x?(a[x]^a[y]):0;}

int main()
{
	scanf("%d",&ttt);
	for (;ttt;ttt--)
	{
		ans=INF;
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d%d",&a[i],&b[i]);
		for (int i=1;i<=n+1;i++)
			for (int j=0;j<(1<<8);j++)
				for (int k=-8;k<=7;k++)
					f[i][j][k+8]=INF;
		f[1][0][7]=0;
		for (int i=1;i<=n;i++)
			for (int j=0;j<(1<<8);j++)
				for (int k=-8;k<=7;k++)
					if (f[i][j][k+8]!=INF)
					{
						if (j&1)
							f[i+1][j>>1][k+7]=min(f[i+1][j>>1][k+7],f[i][j][k+8]);
						else
						{
							last=INF;
							for (int h=0;h<=7;h++)
								if (!(j&(1<<h)))
								{
									if (i+h>last) break;
									last=min(last,i+h+b[i + h]);
									f[i][j|(1<<h)][h+8]=min(f[i][j|(1<<h)][h+8],f[i][j][k+8]+cost(i+k,i+h));
								}
						}
					}
		for (int i=0;i<=8;i++)
			ans=min(ans,f[n+1][0][i]);
		printf("%d\n",ans);
	}
	return 0;
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>
 
using namespace std;

const int MAXN = 13,
		  MAXM = 1005,
		  MAXP = (1<<MAXN),
		  oo = 7000*MAXN*MAXN;

int d[MAXP][MAXN],edge[MAXN][MAXN];
int f[MAXP];
int n,m,ans=oo;

int solve(int root)
{
	memset(d,0,sizeof d);
	for (int i=0;i<MAXP;i++) f[i]=oo;
	f[1<<(root)] = 0;  
	d[(1<<root)][root] = 1;
	int N = 1<<n,x,p;
	for (int i=0;i<N;i++)
		for (int j=0;j<n;j++)
			if ( i& (1<<j) )
			for (int k=0;k<n;k++)
				if ( (!(i&(1<<k))) && (edge[j][k]!=-1) )
				{
					p = (1<<k);
					x = f[i] + d[i][j] * edge[j][k];
					if (f[i+p]>x)
					{
						f[i+p] = x;
						for (int l=0;l<n;l++) d[i+p][l]=d[i][l];
						d[i+p][k]=d[i][j]+1;
					}
				}
	return f[N-1];
}
int main()
{
	int x,y,z;
	memset(edge,-1,sizeof(edge));
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if (edge[x-1][y-1]>z || edge[x-1][y-1]==-1)
			edge[x-1][y-1]=edge[y-1][x-1]=z;
	}
	for (int i=0;i<n;i++)
		ans = min(ans,solve(i));
	printf("%d\n",ans);
	return 0;
}

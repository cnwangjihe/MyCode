#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 100009;

int Val[2][2][18][MAXN];
int a[MAXN],b[MAXN];
int n,m;

void _build()
{
	int k=log2(n);
	for (int i=1;i<=n;i++)
		Val[0][0][0][i]=a[i];
	for (int i=1;i<=k;i++) 
		for (int j=1;j+(1<<i-1)<=n;j++)
			Val[0][0][i][j]=min(Val[0][0][i-1][j],Val[0][0][i-1][j+(1<<i-1)]);

	for (int i=1;i<=n;i++)
		Val[1][0][0][i]=a[i];
	for (int i=1;i<=k;i++) 
		for (int j=1;j+(1<<i-1)<=n;j++)
			Val[1][0][i][j]=max(Val[1][0][i-1][j],Val[1][0][i-1][j+(1<<i-1)]);

	for (int i=1;i<=n;i++)
		b[a[i]]=i;

	for (int i=1;i<=n;i++)
		Val[0][1][0][i]=b[i];
	for (int i=1;i<=k;i++) 
		for (int j=1;j+(1<<i-1)<=n;j++)
			Val[0][1][i][j]=min(Val[0][1][i-1][j],Val[0][1][i-1][j+(1<<i-1)]);

	for (int i=1;i<=n;i++)
		Val[1][1][0][i]=b[i];
	for (int i=1;i<=k;i++) 
		for (int j=1;j+(1<<i-1)<=n;j++)
			Val[1][1][i][j]=max(Val[1][1][i-1][j],Val[1][1][i-1][j+(1<<i-1)]);
	return ;
}

int _askmin(int t,int l,int r)
{
	int k=log2(r-l+1);
	return min(Val[0][t][k][l],Val[0][t][k][r-(1<<k)+1]);
}
int _askmax(int t,int l,int r)
{
	int k=log2(r-l+1);
	return max(Val[1][t][k][l],Val[1][t][k][r-(1<<k)+1]);
}

int main()
{
	freopen("2438.in","r",stdin);
	freopen("2438.out","w",stdout);
	int x,y,p,q;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	_build();
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		for (int p=_askmin(0,x,y),q=_askmax(0,x,y);\
			 q-p!=y-x;\
			 x=_askmin(1,p,q),y=_askmax(1,p,q),p=_askmin(0,x,y),q=_askmax(0,x,y));
		printf("%d %d\n",x,y);
	}
	return 0;
}
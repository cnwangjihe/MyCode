/*
state:Accepted
submit:http://www.lydsy.com/JudgeOnline/
RunID:2606507
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <stdio.h>

using namespace std;

const int MAXN = 100009;

int n,m;
int h[MAXN];
int Max[23][MAXN];

void RMQ()
{
	m=(int)log2(n);
	for (int i=1;i<=n;i++)
		Max[0][i]=h[i];
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			if (j+(1<<i)<=n)
				Max[i][j]=max(Max[i-1][j],Max[i-1][j+(1<<(i-1))]);
	return ;
}

int query(int l,int r)
{
	int len=(int)log2(r-l+1);
	return max(Max[len][l],Max[len][r-(1<<len)+1]);
}

int solve(int pos)
{
	int i=1,j=pos-1,ans=0,len,k;
	for (int i=1,j=pos-1;1;i++,j=k-1)
	{
		len=i*i-(i-1)*(i-1);
		k=max(j-len+1,1);
		if (k>j)
			break;
		ans=max(ans,query(k,j)-h[pos]+i);
		if (k==1)
			break;
	}
	for (int i=1,j=pos+1;1;i++,j=k+1)
	{
		len=i*i-(i-1)*(i-1);
		k=min(n,j+len-1);
		if (k<j)
			break;
		ans=max(ans,query(j,k)-h[pos]+i);
		if (k==n)
			break;
	}
	return ans;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	RMQ();
	for (int i=1;i<=n;i++)
		printf("%d\n",solve(i));
	return 0;
}

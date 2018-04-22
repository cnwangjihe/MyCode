#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 20009,
		  INF  = 2000000009;

int head=0,tail=-1;
int line[MAXN],dis[MAXN],w[MAXN],sum[MAXN];
int ans=INF,tot=0,n;

inline double calc(int j,int k)
{
	return ((double)sum[k]*dis[k]-sum[j]*dis[j])/((double)sum[k]-sum[j]);
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&w[i],&dis[i]);
		sum[i]=sum[i-1]+w[i];
	//	cerr << sum[i] << ' ';
	}
//	cerr << '\n';
	for (int i=n;i;i--)
	{
		dis[i]+=dis[i+1];
		tot+=dis[i]*w[i];
	}
	line[++tail]=1;
	int t;
	for (int i=2;i<=n;i++)
	{
		while (head+1<=tail && calc(line[head],line[head+1])>=dis[i])
			head++;
		t=line[head];
		ans=min(ans,tot-sum[t]*dis[t]-(sum[i]-sum[t])*dis[i]);
		while (tail-1>=head && calc(line[tail],i)>calc(line[tail-1],line[tail]))
			tail--;
		line[++tail]=i;
	}
	printf("%d\n",ans);
	return 0;
}
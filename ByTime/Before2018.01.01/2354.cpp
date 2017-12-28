#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXN = 200006;

int s[MAXN],d[MAXN];
long long ans=0;
int n,g;

int main()
{
	freopen("2354.in","r",stdin);
	freopen("2354.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d%d",&s[i],&g);
		d[i]=s[i]+g;
	}
	for (int i=1;i<n;i++)
		d[i]=min(d[i],d[i-1]+1);
	for (int i=n-2;i>=0;i--)
		d[i]=min(d[i],d[i+1]+1);
	for (int i=0;i<n;i++)
		if (d[i]<s[i]) return printf("-1\n")&0;
			else ans+=(long long)(d[i]-s[i]);
	printf("%lld\n",ans);
	for (int i=0;i<n;i++)
		printf("%d ",d[i]);
	putchar('\n');
	return 0;
}

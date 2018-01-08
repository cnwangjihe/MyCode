#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 5005;

int n,Max=0,ans=0;
int f[MAXN],len[MAXN],a[MAXN];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	len[0]=0,f[0]=0;
	for (int i=1;i<=n;i++)
	{
		len[i]=0,f[i]=0;
		for (int j=0;j<i;j++)
			if (a[i]<a[j] && len[j]>len[i])
				len[i]=len[j];
		for (int j=0;j<i;j++)
		{
			if (a[i]<a[j] && len[j]==len[i])
				f[i]+=f[j];
			if (a[i]==a[j] && len[j]==len[i]+1)
				f[j]=0;
		}
		if (!f[i]) f[i]=1;
		len[i]++;
		Max=max(Max,len[i]);
	}
	for (int i=1;i<=n;i++)
		if (Max==len[i])
			ans+=f[i];
	printf("%d %d\n",Max,ans);
	return 0;
}

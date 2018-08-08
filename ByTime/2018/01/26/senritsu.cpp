#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MaXN = 1009,
			MOD	= 1000000007;

int n,m;
int a[MaXN],cnt[MaXN],p[MaXN],ans[MaXN];

int main()
{
	freopen("senritsu.in","r",stdin);
	freopen("senritsu.out","w",stdout);
	memset(ans,0,sizeof ans);
	memset(cnt,0,sizeof cnt);
	int x,y;
	scanf("%d%d",&n,&m);
	while (m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		cnt[min(x,y)]++;
	}
	for (int i=1;i<=n;i++)
		p[i-1]=i;
	for (int i=1;i<=n;i++)
	{
		a[i] = p[cnt[i]];
		for (int j=cnt[i];p[j+1];j++)
			p[j]=p[j+1];
	}
	a[0]=0;a[n+1]=n+1;
	ans[0]=1;
	for (int i = 1; i <= n + 1; i++)
		for (int j=i-1,k=-1;j>=0;j--)
			if (a[j] > k && a[j] < a[i])
			{
				ans[i]+=ans[j];
				ans[i]%=MOD;
				k=a[j];
			}
	printf("%d\n",ans[n + 1]);
	return 0;
}

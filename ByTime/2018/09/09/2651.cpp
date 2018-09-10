#include<bits/stdc++.h>
using namespace std;

int a[20],f[20][610];
int n,ans;

int main()
{
	freopen("2651.in","r",stdin);
	freopen("2651.out","w",stdout);
	scanf("%d",&n);
	a[0]=1;
	for (int i=1;i<=10;i++)
		scanf("%d",&a[i]);
	f[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		for (int k=0;k<=10;k++)
		    for (int j=600-k;j>=0;j--)
	            f[i][j+k]+=a[k]*f[i-1][j];
	}
	for (int i=0;i<=600;i++)
		if(f[n][i]&1)
			ans++;
	printf("%d\n",ans);;
	return 0;
}
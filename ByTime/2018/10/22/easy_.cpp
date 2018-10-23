#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009,
		  MOD  = 991127;

int n,a[MAXN],g[33],f[MAXN];

int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f[1]=1;
	for (int i=0;i<=30;i++)
		if ((a[1] & (1 << i)))
			g[i]=1;
	for (int i=2;i<=n;i++)
	{
		for (int j=0;j<=30;j++)
			if ((a[i] & (1 << j)))
				f[i]=(f[i]+g[j])%MOD;
		for (int j=0;j<=30;j++)
			if ((a[i] & (1 << j))!=0)
				g[j]=(g[j]+f[i])%MOD;
	}
	printf("%d\n",f[n]);
	return 0;	
}

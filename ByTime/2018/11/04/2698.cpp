#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int a[MAXN],b[32];
int n,m,sum=0;
long long ans=0;

void Add(int v)
{
	for (int i=30;~i;i--)
		if (v&(1<<i))
			if (!b[i]++)
				sum+=(1<<i);
	return ;
}

void Del(int v)
{
	for (int i=30;~i;i--)
		if (v&(1<<i))
			if (!--b[i])
				sum-=(1<<i);
	return ;
}

int main()
{
	freopen("2698.in","r",stdin);
	freopen("2698.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int j=0;
	for (int i=1;i<=n;i++)
	{
		while (j<=n && sum<m)
			Add(a[++j]);
		ans+=max(0,j-i-1);
		Del(a[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
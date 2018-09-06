#include <bits/stdc++.h>

using namespace std;

const int MAXM = 21;

long long v[1<<(MAXM)];
bool vis[MAXM];
int a[MAXM],b[MAXM],c[MAXM];
int n,m,cnt;
long long Max;

long long calc(int s)
{
	long long sum=0;
	memset(vis,0,sizeof vis);
	for (int i=0;i<m;i++)
	{
		if (!((1<<i)&s))
			continue;
		if (vis[a[i]] || vis[b[i]])
			return -1;
		vis[a[i]]=vis[b[i]]=1;
		sum+=c[i];
	}
	return sum;
}

int main()
{
	freopen("2649.in","r",stdin);
	freopen("2649.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		Max=0;
		cnt=0;
		scanf("%d%d",&n,&m);
		for (int i=0;i<m;i++)
			scanf("%d%d%d",&a[i],&b[i],&c[i]);
		for (int i=0;i<(1<<m);i++)
			Max=max(Max,v[i]=calc(i));
		for (int i=0;i<(1<<m);i++)
			cnt+=(v[i]==Max);
		printf("%lld %d\n",Max,cnt);
	}
	return 0;
}
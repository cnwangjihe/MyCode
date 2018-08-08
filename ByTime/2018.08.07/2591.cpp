#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500009;

bool vis[MAXN];
int p[MAXN];
long long sum=0,ans;
long long s[MAXN];
int miu[MAXN];
int n,m=0;

int main()
{
	freopen("2591.in","r",stdin);
	freopen("2591.out","w",stdout);
	int tmp;
	scanf("%d",&n);
	memset(vis,0,sizeof vis);
	miu[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!vis[i])
		{
			p[m++]=i;
			miu[i]=-1;
		}
	//	cerr << i << endl;
		for (int j=0;j<m && p[j]*i<=n;j++)
		{
			tmp=i*p[j];
			vis[tmp]=1;
			if (i%p[j]==0)
			{
				miu[tmp]=0;
				break;
			}
			miu[tmp]=miu[i]*miu[p[j]];
		}
	}
//	for (int i=1;i<=20;i++)
//		printf("miu[%d]=%d\n",i,miu[i]);
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j+=i)
			s[j]+=miu[i]*((long long)n/i);
	s[1]--;
	//forto(i,1,n) printf("%d\n",s[i]); 
	for (int i=1;i<=n;i++)
		sum+=1ll*s[i]*(n-1-s[i]);
	ans = (long long)(n)*(n-1)*(n-2)/6 - sum/2;
	printf("%lld\n",ans);
	return 0;
}

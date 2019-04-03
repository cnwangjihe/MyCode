// Date      : 2019-04-01 16:15:14
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 59;
const long long INF = 1000000000000000009ll;

long long a[MAXN];
long long sum[MAXN],Max[MAXN];
long long g[MAXN];
long long f[MAXN];
long long ans;
int n;
long long k;

int main()
{
	freopen("2843.in","r",stdin);
	freopen("2843.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		scanf("%d%lld",&n,&k);
		for (int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			sum[i]=sum[i-1]+a[i];
			Max[i]=a[i];
		}
		for (int i=1;i<=n;i++)
			for (int j=0;j<i;j++)
				Max[i]=max(Max[i],sum[i]-sum[j]);
		fill(f,f+MAXN,INF);
		fill(g,g+MAXN,0);
	//	if (a[1]>=0)
			f[1]=1,g[1]=a[1];
		long long val,cnt;
		for (int i=2;i<=n;i++)
			for (int j=1;j<i;j++)
			{
				if (f[j]==INF)
					continue;
				val=g[j]+sum[i]-sum[j];
				if (val>=0)
				{
					if (f[i]>f[j] || (f[i]==f[j] && g[i]<val))
						f[i]=f[j],g[i]=val;
				}
				else
				{
					if (Max[j]<=0)
						continue;
					cnt=(-(sum[i]-sum[j]))-g[j]-1;
					cnt=(cnt/Max[j]/2ll+1)*2ll;
					val+=1ll*cnt*Max[j];
					if (f[i]>f[j]+cnt || (f[i]==f[j]+cnt && g[i]<val))
						f[i]=f[j]+cnt,g[i]=val;
				}
			}
	//	cerr << "f88k\n";
		for (int i=1;i<=n;i++)
			if (f[i]<=k)
				ans=max(ans,1ll*(k-f[i])*Max[i]+g[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
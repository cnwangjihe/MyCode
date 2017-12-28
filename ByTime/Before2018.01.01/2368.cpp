#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 10000009;
long long phi[MAXN],f[MAXN];
int n,m,T,phi[MAXN],prim[MAXN],tot,sum,o[MAXN],t1,t2;
long long ans,ans2;

int main()
{
//	freopen("2368.in","r",stdin);
//	freopen("2368.out","w",stdout);
	scanf("%d",&n);
	phi[1]=1;
	for (int i=2;i<=n;i++) 
	{
		if (!o[i]) 
		{
			if ((long long)i*i>(long long)n) t1++;
			if (i*2>n) t2++;
			prim[++tot]=i;
			phi[i]=i-1;
			o[i]=i;
		}
		for (int j=1;j<=tot&&(long long)i*prim[j]<=n;j++)
		{
			o[i*prim[j]]=prim[j];
			if (i%prim[j]==0) { phi[i*prim[j]]=phi[i]*prim[j]; break; } else phi[i*prim[j]]=phi[i]*(prim[j]-1); 
		}
		ans+=(long long)i-phi[i]-1;
		if (o[i]*o[i]<=(long long)n) ans+=((long long)phi[i]-1-t1)*2;
		f[o[i]]++;
	}
	for (int i=1;i<=n;i++) f[i]+=f[i-1];
	for (int i=2;2*i<=n;i++) if ((long long)o[i]*o[i]>n)
	{
		sum=n/i-1;
		ans+=(long long)2*sum+2*((long long)f[n/i]-sum)+3ll*((long long)n-f[n/i]-2-t2);
	}
	t1-=t2;
	printf("%lld\n",ans-(long long)3*(t1-1)*t1/2);
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int mod=1e9+7;
const int mx=1e5+10;
int n;
int a1[mx],a2[mx],a3[mx];
int ans1=0;

void dfs(int k)
{
	if(k==2*n)
	{
		for(int i=1;i<=2*n;i++)
			if(a1[a3[i]]==a1[a3[i+1]]) return ;
		if(a1[a3[1]]==a1[a3[2*n]]) return ;
		ans1++;
/*		for(int i=1;i<=2*n;i++)
			cerr<<a3[i]<<" ";
		cerr<<endl;
*/		return ;
	}
	for(int i=1;i<=2*n;i++)
		if(!a2[i]) a2[i]=1,a3[k+1]=i,dfs(k+1),a2[i]=0;

}

void solve1()
{
	for(int i=1;i<=2*n;i++)
		a1[i]=(i+1)/2;
	dfs(0);
	printf("%d\n",ans1/(2*n));
}

long long f[1005][1005];

void solve2()
{
	f[1][0]=1;
	f[1][1]=0;
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<i;j++)
		{
			int t=2*i-j-1;
			(f[i+1][j]+=f[i][j]*t*(t-1))%=mod;
			(f[i+1][j]+=f[i][j]*j*2)%=mod;
			(f[i+1][j+1]+=f[i][j]*t*2)%=mod;
			if(j>0) (f[i+1][j-1]+=f[i][j]*j*t*2)%=mod;
			if(j>1) (f[i+1][j-2]+=f[i][j]*j*(j-1))%=mod;
		}
	}
	
/*	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			cerr<<i<<" "<<j<<": "<<f[i][j]<<" "<<2*i-j-1<<endl;
*/	
	long long ans=(f[n][1]+f[n][0]*max((2*n-3),0))%mod;
//	(ans*=2)%=mod;
	printf("%lld\n",ans);
}

int main()
{
//	freopen("q.in","r",stdin);
//	freopen("q.out","w",stdout);
	
	scanf("%d",&n);
	if(n<=1000)
	{
		solve2();
		return 0;
	}
	return 0;
}

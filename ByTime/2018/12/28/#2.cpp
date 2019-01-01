#include <bits/stdc++.h>
using namespace std;

const int mod=998244353;
typedef long long ll;
const int mx=1e5+10;
int n,m,c;
ll f[2][mx];

ll power(ll a,int k)
{
	if(!k) return 0;
	if(k==1) return a%mod;
	ll ans=power(a,k/2);
	(ans*=ans)%=mod;
	if(k&1) (ans*=a)%=mod;
	return ans;
}

void task1()
{
	
	f[0][0]=1;
	
	ll inv=power(c,mod-2);
	
	for(int i=1;i<=n;i++)
	{
		int t1=i&1,t2=t1^1;
		for(int j=0;j<=c;j++)
			f[t1][j]=0;
		for(int j=0;j<=c;j++)
		{
			if(j>0) f[t1][j]+=f[t2][j-1]*(c-j+1)%mod*inv%mod;
			if(j<c) f[t1][j]+=f[t2][j+1]*(j+1)%mod*inv%mod;
			f[t1][j]%=mod;
		}
	}
	
	printf("%lld\n",f[n&1][m]);

/*	ll ans=f[n&1][m];
	for(int i=1;i<=1000;i++)
		for(int j=1;j<=1000;j++)
			if(i*power(j,mod-2)%mod==ans)
				return void(cerr<<i<<"/"<<j<<endl);
*/
}

int main()
{
	freopen("chocolate.in","r",stdin);
//	freopen("chocolate.out","w",stdout);
	
	scanf("%d%d%d",&n,&c,&m);
	
	return task1(),0;
	int t1=n&1,t2=m&1;
	if((t1^t2)) return printf("0\n"),0;
	
	
	return 0;
}

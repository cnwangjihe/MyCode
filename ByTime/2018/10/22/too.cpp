#include <bits/stdc++.h>
using namespace std;

const int mod=12345;
const int mx=1005;
int n,m;
int a[mx],b[mx];
int fac[mx],fav[mx];

long long power(long long a,long long k)
{
	if(k==1) return a%mod;
	long long tmp=power(a,k/2);
	(tmp*=tmp)%=mod;
	if(k&1) (tmp*=a)%=mod;
	return tmp;
}

int d2[mx],d3[mx],d4[mx];

long long calc1(int a1,int a2,int a3,int a4)
{
	for(int i=1;i<=a2;i++) d2[i]=1;
	for(int i=1;i<=a3;i++) d3[i]=1;
	for(int i=1;i<=a4;i++) d4[i]=1;
	
	long long tmp=1;
	for(int i=a1;i>=1;i--)
	{
		tmp*=i;
		for(int j=1;j<=a2;j++)
			if(d2[j] && tmp%j==0) tmp/=j,d2[j]=0;
		for(int j=1;j<=a3;j++)
			if(d3[j] && tmp%j==0) tmp/=j,d3[j]=0;
		for(int j=1;j<=a4;j++)
			if(d4[j] && tmp%j==0) tmp/=j,d4[j]=0;
	}
	return tmp%mod;
}

void solve1()
{
	long long ans=0;
	for(int i=0;i<=n;i++)
	{
		if(!b[0] && i>0) continue;
		if(b[0] && i%b[0]) continue;
		for(int j=0;j<=n-i;j++)
		{
			if(!b[1] && j>0) continue;
			if(b[1] && j%b[1]) continue;
			int k=n-i-j;
			if(!b[2] && k>0) continue;
			if(b[2] && k%b[2]) continue;
/*			long long tmp=(fac[n]*fav[i])%mod;
			(tmp*=fav[j])%=mod;
			(tmp*=fav[k])%=mod;

			long long tmp=fac[n]/fac[i]/fac[j]/fac[k];
*/			(ans+=calc1(n,i,j,k))%=mod;
//			cerr<<i<<" "<<j<<" "<<k<<": "<<calc1(n,i,j,k)<<endl;
			
		}
	}
	
//	cerr<<calc1(25,8,8,9)<<endl;
	
	printf("%lld\n",ans);
}

int main()
{
	freopen("too.in","r",stdin);
	freopen("too.out","w",stdout);

	scanf("%d%d",&n,&m);
	
	char ch=0;
	for(int i=0;i<m;i++)
	{
		do scanf("%c",&ch);
		while(!((ch>='A' && ch<='Z') || (ch>='a' && ch<='z')));
		a[i]=ch;
		scanf("%d",&b[i]);
	}

	fac[0]=1;
	for(int i=1;i<=500;i++)
		fac[i]=(1ll*fac[i-1]*i)%mod;

	for(int i=0;i<=500;i++)
		fav[i]=power(fac[i],mod-2);

	if(m==3)
	{
		solve1();
		return 0;
	}

	
	return 0;
}

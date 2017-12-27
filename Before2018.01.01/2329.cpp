#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 1000010;
const long long MOD  = 1000000007ll;

int n,k;
long long tk,sum,ans;
long long f[MAXN];

void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b) exgcd(b,a%b,y,x),y-=a/b*x;
		else x=1,y=0;
	return ;
}
long long ny(long long a)
{
	long long x,y;
	exgcd(a,MOD,x,y);
	return (x+MOD)%MOD;
}

int main()
{
	freopen("2329.in","r",stdin);
	freopen("2329.out","w",stdout);
	scanf("%d%d",&n,&k);
	
	tk=1,sum=0;
	
	f[0]=1;
	for (int i=1;i<=k;i++) 
		f[i]=(f[i-1]*i)%MOD;
	
	for(int i=k;i>=1;i--) 
		sum=(sum+tk*f[i])%MOD,
		tk=(tk*i)%MOD;
	
	for(int i=k+1;i<=n;i++)
	{
		f[i]=sum;
		sum=((sum-(tk*f[i-k])%MOD)*i)%MOD;
		sum=(sum+f[i]+MOD)%MOD;
		tk=(tk*((ny(i-k+1)*i)%MOD))%MOD;
	}
	
	ans=0,tk=1;
	for(int i=n-1;i>=0;i--)
		ans=(ans+tk*f[i])%MOD,
		tk=(tk*max(1,i))%MOD;
	printf("%I64d\n",(tk*n-ans)%MOD);
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 59;
const long long MOD = 1000000007ll;

int a[MAXN],b[MAXN],c[MAXN];
int n;
long long sum1=0,sum2=0,tsum1=0,tsum2=0;
char ch;

int main()
{
	freopen("2679.in","r",stdin);
	freopen("2679.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		do {ch=getchar();}
			while (ch!=48 && ch!=49);
		a[i]=ch-48;
	}
	for (int i=1;i<=n;i++)
	{
		do {ch=getchar();}
			while (ch!=48 && ch!=49);
		b[i]=ch-48;
	}
	memset(c,0,sizeof c);
	for (int i=n;i;i--)
		if (a[i]!=c[i])
		{
			c[i]^=1,c[i-1]^=1;
			sum1+=1ll<<(i-1);
			(tsum1+=(1ll<<(i-1))%MOD)%=MOD;
		}
	memset(c,0,sizeof c);
	for (int i=n;i;i--)
		if (b[i]!=c[i])
		{
			c[i]^=1,c[i-1]^=1;
			sum2+=1ll<<(i-1);
			(tsum2+=(1ll<<(i-1))%MOD)%=MOD;
		}
//	cerr << sum1 << endl;
	printf("%lld\n",(llabs(sum1-sum2))%MOD);
//	printf("%lld\n",(abs(tsum1-tsum2))%MOD);
	return 0;
}
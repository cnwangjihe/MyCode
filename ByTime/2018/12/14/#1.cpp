#include <bits/stdc++.h>
#define pr(p) printf("%lld\n",p)
const int oo=2139063143;
const int N=50;
const int mod=1000000007;
using namespace std;
typedef long long LL;
inline void sc (LL &x)
{
    x=0; static int p; p=1; static char c; c=getchar();
    while (!isdigit(c)) { if (c=='-') p=-1; c=getchar(); }
    while ( isdigit(c)) { x=(x<<1)+(x<<3)+(c-48); c=getchar(); }
    x*=p;
}
LL f[N][N][20010];
LL ksm (LL a,LL b)
{
	LL ans=1;
	while (b)
	{
		if (b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
LL n,d,a[N];
LL jc[100100],inv[100100];
void init ()
{
	jc[0]=inv[0]=1;
	for (LL i=1; i<=100000; i++)
		jc[i]=jc[i-1]*i%mod,inv[i]=ksm (jc[i],mod-2);
}
LL C(LL aa,LL bb) { return jc[aa]*inv[bb]%mod*inv[aa-bb]%mod; }
int main()
{
//	freopen ("2735.in","r",stdin);
//	freopen ("2735.out","w",stdout);

	LL t; sc(t);
	init ();

	cerr << inv[3] << " " << inv[18] << endl;
	while (t--)
	{
		memset (f,0,sizeof (f));
memset (a,0,sizeof (a));
		LL n,d; sc(n),sc(d);
		LL sum=0,ans=0;
		for (LL i=1; i<=d; i++)
			sc(a[i]),sum+=a[i];
		sort (a+1,a+d+1);
		f[0][0][0]=1;
		for (LL i=0; i< d; i++)
		{
			for (LL j=0; j<=i; j++)
			{
				for (LL k=0; k<=sum*2; k++)
				{
					(f[i+1][j+1][k]+=f[i][j][k])%=mod;
					if (j&&k+a[i+1]<=sum*2) (f[i+1][j][k+a[i+1]]+=1LL*(((f[i][j][k]*2)%mod*j)%mod))%=mod;
					if (j> 1&&k+a[i+1]*2<=sum*2) (f[i+1][j-1][k+a[i+1]*2]+=1LL*((f[i][j][k]%mod)*((j-1)*j)%mod)%mod)%=mod;
				}
			}
		}
		//pr(sum);
		for (LL dis=sum-a[1]+1; dis<=sum*2; dis++)
			//pr(f[d][1][dis-1]),
			(ans+=1LL*(f[d][1][dis-1]*C(n-dis+d,d)%mod)%mod)%=mod;
		pr(ans);
	}

	return 0;
}

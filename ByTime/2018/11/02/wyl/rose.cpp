#include<bits/stdc++.h>

using namespace std;

const int MAXN = 4009,
		  MOD  = 1073741824;

int f[MAXN][MAXN];
long long sum[MAXN][MAXN],sum1[MAXN][MAXN],sum2[MAXN][MAXN];
int n,m;
long long ans;

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

int gcd(int a,int b) {return a%b?gcd(b,a%b):b;}

int main()
{
	freopen("rose.in","r",stdin);
	freopen("rose.out","w",stdout);

	int T;
	for (int i=1;i<MAXN;i++)
		for (int j=1;j<MAXN;j++)
			if (gcd(i,j)==1)
				f[i][j]=1;

	for (int i=1;i<MAXN;i++)
		for (int j=1;j<MAXN;j++)
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+f[i][j];

	for (int i=1;i<MAXN;i++)
		for (int j=1;j<MAXN;j++)
				sum1[i][j]=(sum1[i][j-1]+sum[i][j-1])%MOD;

	for (int i=1;i<MAXN;i++)
		for (int j=1;j<MAXN;j++)
			sum2[i][j]=(sum1[i][(j+1)/2]*2)%MOD;

	T=read();
	for (int cn=1;cn<=T;cn++)
	{
		n=read(),m=read();
		ans=n+m;
		for (int i=1;i<=n;i++)
			(ans+=(sum1[i-1][m]-sum2[min(i-1,n-i)][m]+MOD+sum1[n-i][m]-sum2[min(i-1,n-i)][m]+MOD)%MOD)%=MOD;		
		printf("%lld\n",ans);
	}
	return 0;
}
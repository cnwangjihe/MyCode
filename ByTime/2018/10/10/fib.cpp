#include <bits/stdc++.h>

using namespace std;

const int MAXN = 90;
const long long MAXV = 1000000000000000000ll;

long long a[MAXN],b[MAXN];
long long f[MAXN];
int m,k;
long long n,sum;

int main()
{
//	freopen("fib.in","r",stdin);
//	freopen("fib.out","w",stdout);
	int T;
	scanf("%d",&T);
	a[1]=a[2]=1;
	m=0;
	for (int i=3;!m && i<MAXN;i++)
	{
		a[i]=a[i-2]+a[i-1];
		if (a[i]>MAXV)
			m=i-1;
	}
	for (int cn=1;cn<=T;cn++)
	{
		k=0;
		scanf("%lld",&n);
		for (int i=m;i>1;i--)
			if (n>=a[i])
				n-=a[i],b[++k]=i;
		for (int i=1;i<=k/2;i++)
			swap(b[i],b[k-i+1]);
		sum=1;
		f[1]=(b[1]-2)/2ll;
		for (int i=2;i<=k;i++)
		{
			f[i]=sum*((b[i]-1-b[i-1])/2ll);
			f[i]+=f[i-1]*((b[i]-b[i-1])/2ll);
			sum+=f[i-1];
			cerr << f[i] << endl;
		}
		printf("%lld\n",f[k]+sum);
	}
	return 0;
}
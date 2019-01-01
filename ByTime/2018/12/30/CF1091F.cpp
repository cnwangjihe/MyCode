// Date      : 2018-12-30 23:22:55
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100009;

long long a[MAXN],sum[MAXN];
long long sum1[MAXN],sumGW[MAXN],sum2[MAXN],sumL[MAXN];
int b[MAXN];
int n;
char c;

int main()
{
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for (int i=1;i<=n;i++)
	{
		do {c=getchar();}
			while (c!='G' && c!='W' && c!='L');
		b[i]=(c=='G'?0:(c=='W'?1:2));
		if (b[i]==2)
		{
			sumL[i]=sumL[i-1]+a[i];
			sum1[i+1]=sumL[i-1]*2+sumGW[i-1]*3;
		}
		else
		{
			sumGW[i]+=sumGW[i]+a[i];
			sum2[i]=sum1[i]+sumGW[i];
		}
	}
	int Left=sum2[n]-sum1[n];
	for (int i=n-1;i;i--)
	{
		if (Left==0)
			continue;
		if (sumGW[i])
		{
			printf("%d",i);
		}

	}
	return 0;
}
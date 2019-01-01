// Date      : 2018-12-30 22:50:05
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 200009;

long long a[MAXN];
int n,m=0;

int main()
{
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	scanf("%d",&n);
	for (int i=1,j;1ll*i*i<=n;i++)
	{
		if (n%i)
			continue;
		a[m++]=1ll*(1+n-i+1)*(n/i)/2;
		if (1ll*i*i!=n)
		{
			j=n/i;
			a[m++]=1ll*(1+n-j+1)*(n/j)/2;
		}
	}
	std::sort(a,a+m);
	for(int i=0;i<m;++i)
		if (i==0 || a[i]!=a[i-1])
			printf("%lld ",a[i]);
	
	return 0;
}
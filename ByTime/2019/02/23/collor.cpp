// Date      : 2019-02-23 08:20:22
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int n,m,k;
long double a,b,d,s,ans=0;

int main()
{
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			a=i*j,b=(n-i+1)*(n-j+1);
			d=1.0*a*b/(1.0*n*n);
			s=0;
			for (int p=0;p<k;p++)
				s=d*(1-s)+s;
			ans+=s;
		}
	}
	printf("%.8Lf\n",ans);
	return 0;
}
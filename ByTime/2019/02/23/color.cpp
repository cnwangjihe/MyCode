// Date      : 2019-02-23 08:20:22
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int n,m,k;
double a,b,c,d,g,s,ans=0;

template<typename T> T qpow(T a,int k)
{
	T ans=1;
	for (int i=0;(1<<i)<=k;a*=a,i++)
		if (k&(1<<i))
			ans*=a;
	return ans;
}

int main()
{
	freopen("2805.in","r",stdin);
	freopen("2805.out","w",stdout);
	int T;
	for (scanf("%d",&T);T;T--)
	{
		scanf("%d%d%d",&k,&n,&m);
		ans=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			{
				a=(i-1),b=(j-1),c=(n-i),d=(m-j);
				g=a*b*(c*d+c+d)+a*(c*d+c+d+b+b*c)+b*(c*d+c+d+a+a*d)+c*d*(a*b+a+b)+c*(a*b+a+b+d+a*d)+d*(a*b+a+b+c+b*c)+b*c*(a*d+d+a)+a*d*(b*c+b+c)+2*n*m-1;
				g=g/(1.0*n*m*n*m);
				ans+=1-qpow(1.0-g,k);
			}
		}
		printf("%.10lf\n",ans);
	}
	return 0;
}
// Date      : 2019-02-23 09:24:34
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int n,m,ans=0;

int main()
{
//	freopen("#1.in","r",stdin);
//	freopen("#1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int x=1;x<=n;x++)
				for (int y=1;y<=m;y++)
				{
					ans+=(abs(x-i)+1)*(abs(y-j)+1);
				}
	printf("%.10lf\n",1.0*ans/(1.0*n*m*n*m));
	return 0;
}
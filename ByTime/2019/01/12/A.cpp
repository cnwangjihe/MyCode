// Date      : 2019-01-11 22:34:05
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int q,l,r,d;

int main()
{
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf("%d%d%d",&l,&r,&d);
		if (d<l)
			printf("%d\n",d);
		else
			printf("%d\n",(r/d+1)*d);
	}
	return 0;
}
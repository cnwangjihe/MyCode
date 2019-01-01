// Date      : 2018-12-30 22:34:41
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int a,b,c;

int main()
{
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	scanf("%d%d%d",&a,&b,&c);
	c-=2;b-=1;
	if (min(min(a,b),c)<0)
		return printf("0\n"),0;
	printf("%d\n",min(min(a,b),c)*3+3);
	return 0;
}
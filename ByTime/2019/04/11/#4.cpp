// Date      : 2019-04-11 15:10:12
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int main()
{
//	freopen("#1.in","r",stdin);
	freopen("#1.out","w",stdout);
	int n=1000,f,last;
	for (int i=1;i<=n;i++)
	{
		last=0;
		f=0;
		for (int j=i;j>=1 && !f;j--)
			if ((i/j)!=last+1 && (i/j)!=last)
				printf("%d\n",last+1),f=1;
			else
				last=i/j;
		if (!f)
			printf("%d\n",i+1);
	}
	return 0;
}
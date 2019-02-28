// Date      : 2019-02-21 08:14:13
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
//	freopen("#1.out","w",stdout);
	for (int i=0;i<=100000;i++)
	{
		int v=i,w=i;
		bool flag=1;
		while (v)
		{
			if (v%10!=w%2)
			{
				flag=0;
				break;
			}
			v/=10,w/=2;
		}
		if (flag)
			printf("%d\n",i);
	}
	return 0;
}
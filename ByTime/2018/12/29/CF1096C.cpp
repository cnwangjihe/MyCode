// Date      : 2018-12-28 22:56:27
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1096/problem/C
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int T,v;

int main()
{
//	freopen("CF1096C.in","r",stdin);
//	freopen("CF1096C.out","w",stdout);
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d",&v);
		v*=2;
		for (int i=3;i<=360;i++)
			if(i*v%360==0 && 360/i!=(360-v))
			{
				printf("%d\n",i);
				break;
			}
	}
	return 0;
}
// Date      : 2018-12-28 22:30:20
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1096/problem/A
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int main()
{
//	freopen("CF1096A.in","r",stdin);
//	freopen("CF1096A.out","w",stdout);
	int T;
	int l,r;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d%d",&l,&r);
		printf("%d %d\n",l,l*2);
	}
	return 0;
}
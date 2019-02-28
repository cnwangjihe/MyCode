// Date      : 2019-01-11 23:23:33
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int T;

int main()
{
//	freopen("E.in","r",stdin);
//	freopen("E.out","w",stdout);
	scanf("%d",&T);
	char c[10];int x,y;
	int tx=0,ty=0;
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%s %d%d",c,&x,&y);
		if (x>y)
			swap(x,y);
		if (c[0]=='+')
			tx=max(tx,x),ty=max(ty,y);
		else
			printf("%s\n",(tx<=x && ty<=y)?"YES":"NO");
	}
	return 0;
}
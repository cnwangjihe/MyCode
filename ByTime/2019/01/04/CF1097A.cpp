// Date      : 2019-01-04 22:31:35
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://codeforces.com/contest/1097/problem/A
// Algorithm : None
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

char s[100],a[100];

int main()
{
//	freopen("CF1097A.in","r",stdin);
//	freopen("CF1097A.out","w",stdout);
	scanf("%s\n",s);
	int flag=0;
	for (int i=0;i<5 && !flag;i++)
	{
		scanf("%s",a);
		if (a[0]==s[0] || a[1]==s[1])
			flag=1;
	}
	printf("%s\n",flag?"YES":"NO");
	return 0;
}
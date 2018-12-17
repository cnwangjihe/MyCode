// Date    : 2018-12-16 21:54:21
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

double ans,explen=0;
char c;
int n;

int main()
{
//	freopen("P1365.in","r",stdin);
//	freopen("P1365.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		do {c=getchar();}
			while (c!='?' && c!='o' && c!='x');
		if (c=='x')
			explen=0;
		else if (c=='o')
			ans+=explen*2+1,explen+=1;
		else if (c=='?')
			ans+=(explen*2+1)/2,explen=(explen+1)/2;
	}
	printf("%.4lf\n",ans);
	return 0;
}
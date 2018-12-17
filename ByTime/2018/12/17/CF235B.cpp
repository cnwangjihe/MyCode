// Date    : 2018-12-17 12:17:21
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

double ans,explen=0,p;
int n;

int main()
{
//	freopen("CF235B.in","r",stdin);
//	freopen("CF235B.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lf",&p);
		ans+=(explen*2+1)*p;
		explen=(explen+1)*p;
	}
	printf("%.15lf\n",ans);
	return 0;
}
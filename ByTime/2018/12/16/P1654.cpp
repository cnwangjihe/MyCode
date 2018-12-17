// Date    : 2018-12-16 22:14:19
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

int n;
double p,expx1,expx2,ans=0;

int main()
{
//	freopen("P1654.in","r",stdin);
//	freopen("P1654.out","w",stdout);
	scanf("%d",&n);
	expx1=expx2=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%lf",&p);
		ans+=(3*expx2+3*expx1+1)*p;
		expx2=(expx2+expx1*2+1)*p;
		expx1=(expx1+1)*p;
	}
	printf("%.1lf\n",ans);
	return 0;
}
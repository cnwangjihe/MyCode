#include <bits/stdc++.h>

using namespace std;

int ans;
long long n;

int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		ans=3;
		scanf("%lld",&n);
		if (n%2==0)
			ans=2;
		if (ans==3)
		{
			ans=2;
			for (long long i=2;i*i<=(n-2);i++)
				if ((n-2)%i==0)
				{
					ans=3;
					break;
				}
		}
		printf("%d\n",ans);
	}
	return 0;
}
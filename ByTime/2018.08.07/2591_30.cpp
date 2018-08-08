#include <bits/stdc++.h>

using namespace std;

int n,ans=0;

int main()
{
	freopen("2591.in","r",stdin);
	freopen("2591.out","w",stdout);
	scanf("%d",&n);
	for (int a=1;a<=n;a++)
		for (int b=a+1;b<=n;b++)
			for (int c=b+1;c<=n;c++)
				if ((__gcd(a,b)==1 && __gcd(a,c)==1 && __gcd(b,c)==1)
				 || (__gcd(a,b)>1 && __gcd(a,c)>1 && __gcd(b,c)>1))
					ans++;
	printf("%d\n",ans);
	return 0;
}
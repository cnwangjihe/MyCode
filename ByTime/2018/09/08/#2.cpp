#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
const int maxn = 40 + 10;

int n,a[maxn];

int main()
{
	int i,ap,rst;
	ll fans=1;
	
	scanf("%d",&n);
	for(i=0;i<n-1;i++) scanf("%d",a+i);
	
	for(i=1;i<n;i++) fans=fans*i%mod;
	for(i=1;i<=n-2;i++) fans=fans*n%mod;
	ap=rst=0;
	for(i=1;i<=(n*(n-1)>>1);i++)
	{
		if(i==a[ap])
		{
			ap++;
			rst+=ap-1;
		}
		else
		{
			fans=fans*rst%mod;
			rst--;
		}
	}
	
	printf("%lld\n",fans);
	
	return 0;
}
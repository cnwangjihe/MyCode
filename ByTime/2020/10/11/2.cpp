#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAXN = 200008;

long long a[MAXN];

int n,k;


bool _cmp(long long a,long long b)
{
	return a>b;
}

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&n,&k);
		for (int i=0;i<n;i++)
			scanf("%lld",&a[i]);
		sort(a,a+n,_cmp);
		for (int i=1;i<n && i<=k;i++)
		{
			a[0]+=a[i];
		}
		printf("%lld\n",a[0]);
	}
	return 0;
}
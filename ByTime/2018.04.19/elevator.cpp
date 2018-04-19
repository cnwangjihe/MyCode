#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 50009;
const long long INF = 10000000000000009ll;

struct Tman {long long t,v;};

int n;
long long f[MAXN];
long long Max;
Tman a[MAXN];
int line[MAXN];

int main()
{
	freopen("elevator.in","r",stdin);
	freopen("elevator.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lld%lld",&a[i].t,&a[i].v);
	f[0]=0;
	for (int i=1;i<=n;i++)
	{
		f[i]=INF;
		Max=a[i].v;
		for (int j=i-1;~j;j--)
		{
			f[i]=min(f[i],Max*2ll+max(f[j],a[i].t));
			Max=max(Max,a[j].v);
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}

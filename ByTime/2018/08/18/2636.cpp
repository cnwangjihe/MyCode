#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

long long ans,t;
int a[MAXN],b[MAXN];
int n;

int main()
{
	freopen("2636.in","r",stdin);
	freopen("2636.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for (int i=0;i<n;i++)
		scanf("%d",&b[i]);
	int al=0,ar=n-1,posb=n-1;
	while (1)
	{
		while (al<=ar && !a[al])
			al++;
		while (al<=ar && !a[ar])
			ar--;
		while (~posb && !b[posb])
			posb--;
		if (al>ar || posb==-1)
			break;
		if (ar>=posb)
		{
			t=min(a[ar],b[posb]);
			ans+=t*(ar-posb);
			a[ar]-=t,b[posb]-=t;
		}
		else
		{
			t=min(a[al],b[posb]);
			ans+=t*(al+posb);
			a[al]-=t,b[posb]-=t;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
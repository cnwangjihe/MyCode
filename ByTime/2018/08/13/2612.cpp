#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;

int ans=0,n;
pair<int,int> a[MAXN];

int main()
{
	freopen("2612.in","r",stdin);
	freopen("2612.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	sort(a+1,a+1+n);
	for (int i=1;i<=n;i++)
		ans+=(a[i].first-a[i-1].first)*a[i].second*a[i].second;
	printf("%d\n",ans);
	return 0;
}
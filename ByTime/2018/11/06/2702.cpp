#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int a[MAXN],b[MAXN];
long long sum,ans;
int n;

int main()
{
	freopen("2702.in","r",stdin);
	freopen("2702.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
		b[i]=abs(a[i]-a[i+1]);
	b[n]=0;
	int l=1;
	sum=b[l];
	ans=max(sum,ans);
	for (int i=l+1;i+1<=n;i+=2)
	{
		if (sum-b[i]<=0)
			sum=b[i+1];
		else
			sum+=b[i+1]-b[i];
	//	cerr << "## " << i << ' ' << sum << endl; 
		ans=max(sum,ans);
	}
	l=2;
	sum=b[l];
	ans=max(sum,ans);
	for (int i=l+1;i+1<=n;i+=2)
	{
		if (sum-b[i]<=0)
			sum=b[i+1];
		else
			sum+=b[i+1]-b[i];
	//	cerr << "## " << i << ' ' << sum << endl; 
		ans=max(sum,ans);
	}
	printf("%lld\n",ans);
	return 0;
}
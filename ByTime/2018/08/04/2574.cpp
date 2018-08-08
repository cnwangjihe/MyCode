#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;
const long long INF = 10000000009;

long long sum,ans=INF;
long long Max1=0,Max2=0,cnt1,cnt2;
long long a[MAXN];
int n;

long long calc(int pos)
{
	long long t1 = 0, t2 = sum;
	if (a[pos] > 0)
		t2 = Max1 + 1;
	if (cnt1 > 1)
		t1=(a[pos]==Max1?Max1+1:(a[pos]==Max1-1?sum:(a[pos]<Max1-1?sum-Max1:0)));
	else
		t1=(a[pos]==Max1-1?sum:(a[pos]==Max1-2?(Max2==Max1-1?(Max1-1)*(cnt2+2):(Max1-1)*2):(a[pos]<Max1-2?(Max2==Max1-1?(Max1-1)*(cnt2+1):Max1-1):0)));
	return min(t1,t2);
}

int main()
{
	freopen("2574.in","r",stdin);
	freopen("2574.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%lld",&a[i]);
		if (a[i]>Max1)
			Max1=a[i],cnt1=1;
		else
			cnt1+=(a[i]==Max1);
	}
	for (int i=0;i<n;i++)
	{
		if (a[i]==Max1)
			continue;
		if (a[i]>Max2)
			Max2=a[i],cnt2=1;
		else
			cnt2+=(a[i]==Max2);
	}
	sum=(long long)Max1*cnt1;
	ans=sum;
	for (int i=0;i<n;i++)
	{
		if (a[i]!=Max1)
			continue;
		if (i!=0)
			ans=min(ans,calc(i-1));
		if (i!=n-1)
			ans=min(ans,calc(i+1));
	}
	printf("%lld\n",ans);
	return 0;
}
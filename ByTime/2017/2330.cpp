#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

int n,s1,s2;
int a[100009];

bool _check(int len)
{
	int l=a[n]-len,r=a[n]+len;
	for (int i=n-1;i>=1;i--)
		if (a[i]>=l && a[i]<=r) l=a[i]-len,r=a[i]+len;
			else l=max(l,a[i]-len),r=min(r,a[i]+len);
	return ((l<=s1 && s1<=r) || (l<=s2 && s2<=r));
} 
int main()
{
	freopen("2330.in","r",stdin);
	freopen("2330.out","w",stdout);
	scanf("%d%d%d",&n,&s1,&s2);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if (s1>s2) swap(s1,s2);
	
	int l=s2-s1-1,r=1000000009,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (_check(mid)) r=mid;
			else l=mid;
	}
	printf("%d\n",r);
	return 0;
}

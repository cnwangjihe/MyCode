#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100009;

long long n,a,d,tmp,k,ans=0,now=0,Max=0,cnt;
long long t[MAXN];
bool flag=0;
int m;

int main()
{
	freopen("2344.in","r",stdin);
	freopen("2344.out","w",stdout);
	scanf("%lld%d%lld%lld",&n,&m,&a,&d);
	long long x=d/a+1;
	for (int i=0;i<m;i++)
	{
		scanf("%lld",&t[i]);
		if (t[i]>Max) Max=t[i];
	}
	t[m++]=max(n*a,Max)+2*d;
//	sort(t,t+m);
	if (t[0]<a) now=t[0]+d;
		else now=a+d;
	k=now/a+1;
	for (int i=0;i<m;i++)
	{
		if (k>n)
		{
			cnt=i;
			flag=1;
			break;
		}
		if (t[i]<=now) continue;
		if (t[i]<=k*a)
		{
			ans++; 
			now=t[i]+d;
			k=now/a+1;
		}
		else
		{
			tmp=min(t[i]/a,n)-k;
			ans+=tmp/x+1;
			now=(k+(tmp/x+1)*x)*a-a+d%a;
			k+=(tmp/x+1)*x;
			if (t[i]<=now) continue;
			ans++; now=t[i]+d;
			k=now/a+1;
		}
	}
	if (flag)
	{
		for (int i=cnt;i<m;i++)
			if (t[i]>now) ans++,now=t[i]+d;
	}
	printf("%lld\n",ans);
	return 0;
}

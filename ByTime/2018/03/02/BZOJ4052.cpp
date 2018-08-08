/*
state:Accepted
submit:local
RunID:NULL
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 10009;

struct Tnum
{
	int i;
	long long v;
}a[MAXN];

int n,m;
long long ans;

long long gcd(long long a,long long b) {return !b?a:gcd(b,a%b);}

int main()
{
	int ttt,k;
	long long val;
	scanf("%d",&ttt);
	for (;ttt;ttt--)
	{
		scanf("%d",&n);
		ans=0ll;
		m=0;
		for (int i=0;i<n;i++)
		{
			k=0;
			scanf("%lld",&val);
			a[m++]=(Tnum){i,0};
			for (int j=0;j<m;j++)
				a[j].v=gcd(a[j].v,val);
			for (int j=0;j<m;j++)
				if (j==1 || a[j].v!=a[j-1].v)
					a[k++]=a[j];
			for (int j=0;j<k;j++)
				ans=max(ans,a[j].v*(i-a[j].i+1));
			m=k;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

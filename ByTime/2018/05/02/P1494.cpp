#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

struct Task{int x,y,i;};

const int MAXN = 50009,
		  MAXM = MAXN;

int n,m;
int a[MAXN],cnt[MAXN];
long long ans[MAXM],len[MAXM];
Task q[MAXM];

bool _cmpx(Task a,Task b){return a.x<b.x;}
bool _cmpy(Task a,Task b){return a.y==b.y?a.x<b.x:a.y<b.y;}
long long gcd(long long a,long long b){return a%b==0ll?b:gcd(b,a%b);}

int main()
{
	int r,al,ar,step;
	long long sum;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&q[i].x,&q[i].y);
		q[i].i=i;
	}
	sort(q,q+m,_cmpx);
	step=int(sqrt(n));
	al=ar=0;
	for (int l=1;l<=n;l+=step)
	{
		memset(cnt,0,sizeof cnt);
		r=min(n,l+step);
		al=ar;
		sum=0ll;
		while (q[ar].x<r && ar<m)
			ar++;
		if (al==ar)
			continue;
		sort(q+al,q+ar,_cmpy);
		for (int i=q[al].x;i<=q[al].y;i++)
			sum+=(long long)cnt[a[i]],cnt[a[i]]++;
		ans[q[al].i]=sum;
		len[q[al].i]=q[al].y-q[al].x+1;
		for (int i=al+1;i<ar;i++)
		{
			for (int j=q[i-1].y+1;j<=q[i].y;j++)
				sum+=(long long)cnt[a[j]],cnt[a[j]]++;
			if (q[i].x<=q[i-1].x)
				for (int j=q[i].x;j<q[i-1].x;j++)
					sum+=cnt[a[j]],cnt[a[j]]++;
			else
				for (int j=q[i-1].x;j<q[i].x;j++)
					cnt[a[j]]--,sum-=(long long)cnt[a[j]];
			ans[q[i].i]=sum;
			len[q[i].i]=q[i].y-q[i].x+1;
		}
	}
	long long t1,t2,t3;
	for (int i=0;i<m;i++)
	{
		if (ans[i]==0)
		{
			printf("0/1\n");
			continue;
		}
		t1=ans[i]*2ll,t2=len[i]*(len[i]-1),t3=gcd(t1,t2);
		printf("%lld/%lld\n",t1/t3,t2/t3);
	}
	return 0;
}
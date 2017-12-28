#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 200009;

int n,k;
int rmq[MAXN][32],orsum[MAXN][32];
int a[MAXN],d[MAXN];
long long ans;

void _init()
{
	for (int i=1;i<=n;i++){rmq[i][0]=a[i];orsum[i][0]=a[i];}
	for (int i=1;(1 << i)<=n;i++)
		for (int j=1;j+(1 << i)-1<=n;j++)
		{
			rmq[j][i]=max(rmq[j][i-1],rmq[j+(1 << (i-1))][i-1]);
			orsum[j][i]=orsum[j][i-1] | orsum[j+(1 <<(i-1))][i-1];
		}
	k=2;
	for (int i=2;i<=n;i++)
		d[i]=d[i-1]+(i==k),k*=1+(i==k);
}
int qmax(int l,int r)
{
	return max(rmq[l][d[r-l+1]],rmq[r-(1 << d[r-l+1])+1][d[r-l+1]]);
}
int qor(int l,int r)
{
	return (orsum[l][d[r-l+1]] | orsum[r-(1 << d[r-l+1])+1][d[r-l+1]]);
}
void solve(int k)
{
	long long l=0,r=k,mid;
	long long head1,head2,tail1,tail2;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (qmax(mid,k-1)<a[k]) r=mid;
			else l=mid;
	}
	head1=r;
	l=k,r=n+1;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (qmax(k+1,mid)<=a[k]) l=mid;
			else r=mid;
	}
	tail1=l;
	l=1,r=k;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if ((qor(mid,k-1) | a[k])>a[k]) l=mid;
			else r=mid;
	}
	head2=max(l,head1);
	if ((qor(head2,k) | a[k])==a[k]) head2--;
	l=k,r=n;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if ((qor(k+1,mid) | a[k])>a[k]) r=mid;
			else l=mid;
	}
	tail2=min(r,tail1);
	if ((qor(k,tail2) | a[k])==a[k]) tail2++;
	ans+=(k-head1+1)*(tail1-k+1)-(k-head2)*(tail2-k);
}
int main()
{
	freopen("2334.in","r",stdin);
	freopen("2334.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	_init();
	for (int i=1;i<=n;i++)
		solve(i);
	printf("%lld\n",ans);
	return 0;
}

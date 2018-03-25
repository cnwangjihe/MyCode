#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 502;

struct Tnum
{
	int i,v;
	Tnum() {i=v=0;} 
}a[MAXN],b[MAXN];

int n;

void solve(int l,int r,int k)
{
	if ( k>(1<<29)  || l>=r) return;
	int tl=l,tr=r;
	for (int i=l;i<=r;i++)
		if (a[i].v & k) b[tl++]=a[i];
			else b[tr--]=a[i];
	for (int i=l;i<=r;i++) a[i]=b[i]; 
	solve(l,tl-1,k*2);
	solve(tr+1,r,k*2);
	return ;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].v);
		a[i].i=i;
	}
	solve(1,n,1);
	for (int i=1;i<=n;i++)
		printf("%d ",a[i].i);
	return 0;
}

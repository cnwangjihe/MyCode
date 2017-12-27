#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 25;

int a[MAXN],ans[MAXN],p[MAXN];
int n;

bool _cmp(int x,int y) {return a[x]<a[y];}

int main()
{
	freopen("2342.in","r",stdin);
	freopen("2342.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		p[i]=i;
	}
	sort(p,p+n,_cmp);
	for(int i=0;i<n-1;i++)
		ans[p[i+1]]=a[p[i]];
	ans[p[0]]=a[p[n-1]];
	for(int i=0;i<n;i++)
		printf("%d ",ans[i]);
	return 0;
}

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <fstream>

using namespace std; 

const int MAXN = 1000010;

int n,u,v;
long long ans;
int cnt[MAXN]; 

int main()
{
	freopen("2081.in","r",stdin);
	freopen("2081.out","w",stdout);
	ans=1;
	scanf("%d",&n);
	for(int i=1;i<n;i++) 
	{
		scanf("%d%d",&u,&v);
		cnt[u]++;cnt[v]++;
	}
	for(int i=1;i<=n;i++) 
		if (cnt[i]>2) ans=ans+(cnt[i]-2)*2;
	printf("%lld\n",ans);
	return 0;
}

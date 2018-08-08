#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <map>

using namespace std;

const int MAXN = 300009,
		  INF  = 0x7fffffff;

map<int,int> _in;
int a,b,n,ans=INF,fp=0;
int cnt[MAXN],cnt1[MAXN];

int main()
{
	freopen("2463.in","r",stdin);
	freopen("2463.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		if (!_in.count(a))
			_in[a]=fp++;
		if (!_in.count(b))
			_in[b]=fp++;
		cnt1[_in[a]]++,cnt[_in[a]]++,cnt[_in[b]]++;
	}
	for (int i=0;i<fp;i++)
	{
		if (cnt[i]<(n+1)/2)
			continue;
		ans=min(ans,max(0,(n+1)/2-cnt1[i]));
	}
	if (ans==INF)
		printf("Impossible\n");
	else
		printf("%d\n",ans);
	return 0;
}
// Date    : 2018-12-21 14:37:02
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std; //not suggest anymore.Please use std::

const int MAXL = 100,
		  MAXN = 10000009;

bool t[MAXN];
std::set<long long> f;
int n;
long long ans;

int main()
{
	freopen("ernd.in","r",stdin);
	freopen("ernd.out","w",stdout);
	scanf("%d",&n);
	n++;
	t[0]=0;
	for (int i=0;i<10000;i++)
		t[i*2]=t[i],t[i*2+1]=1-t[i];
	long long x;
	for (int i=0;i<2000;i++)
	{
		x=0;
		for (int j=0;j<63;j++)
		{
			x=(x<<1ll)+1ll*t[i+j];
			f.insert(x);
		}
	}
	for (set<long long>::iterator i=f.begin();i!=f.end() && n;i++)
	{
		n--;
		ans=*i;
	}
	printf("%lld\n",ans);
	return 0;
}
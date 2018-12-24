// Date    : 2018-12-24 07:47:31
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 200009,
		  INF  = 1<<30;

struct Tnode {int l,r;};

Tnode a[MAXN];
int n,ans=0;

bool _cmp(Tnode a,Tnode b){return (a.r==b.r)?(a.l<b.l):(a.r<b.r);}

int main()
{
//	freopen("CF527D.in","r",stdin);
//	freopen("CF527D.out","w",stdout);
	int x,w;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d%d",&x,&w);
		a[i].l=x-w,a[i].r=x+w;
	}
	std::sort(a,a+n,_cmp);
	int r=-INF;
	for (int i=0;i<n;i++)
	{
		if (a[i].l>=r)
		{
			ans++;
			r=a[i].r;
		}
	}
	printf("%d\n",ans);
	return 0;
}
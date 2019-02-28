// Date      : 2019-01-11 22:58:28
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100009;

struct Tnode{int l,r,i;};

int c[MAXN];
int p[MAXN];
Tnode a[MAXN];
int T,n;


bool _cmp(Tnode a,Tnode b){return a.l<b.l || (a.l==b.l && a.r<b.r);}

int main()
{
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	scanf("%d",&T);
	for (int cn=0;cn<T;cn++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d%d",&a[i].l,&a[i].r),a[i].i=i;
		std::sort(a+1,a+n+1,_cmp);
		for (int i=1;i<=n;++i) c[i]=-1;

		for (int i=1,j=0;i<=n;i++)
		{
			if (a[i].l>=a[j].l && a[i].r<=a[j].r)
			{
				c[a[i].i]=c[a[j].i];
				continue;
			}
			if (a[i].l>a[j].r)
				c[a[i].i]=c[a[j].i]^1;
			else
				c[a[i].i]=c[a[j].i];
			j=i;
		}
		bool fg=0;
		for (int i=1;i<=n && (!fg);i++)
			if (c[a[i].i]==0)
				fg=1;
		if (!fg)
		{
			printf("-1\n");
			continue;
		}
		for(int i=1;i<=n;i++)
			printf("%d ",c[i]+1);
		printf("\n");
	}
	return 0;
}
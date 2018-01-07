#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

const int INF = 0x3f3f3f3f,
		   MAXN = 1000005;
		   
struct Tnode { int Add,Max; Tnode(){Add=Max=0;}};
struct Tdata { int l,r; };

Tdata s[MAXN];
Tnode tree[MAXN*4];
int n,m,fp=0,ans=INF;
int p[MAXN];

int pos(int x) { return lower_bound(p+1, p+fp+1, x) - p; }
bool _cmp(Tdata u,Tdata v) { return u.r - u.l < v.r - v.l; }

void _down(int u)
{
	tree[u*2].Add+=tree[u].Add;
	tree[u*2+1].Add+=tree[u].Add;
	tree[u*2].Max+=tree[u].Add;
	tree[u*2+1].Max+=tree[u].Add;
	tree[u].Add=0;
	return ;
}

void _add(int u,int l,int r,int al,int ar,int v)
{
	if (al<=l && ar>=r)
	{
		tree[u].Add+=v;
		tree[u].Max+=v;
		return ;
	}
	_down(u);
	int mid=(l+r)/2;
	if (al<=mid) _add(u*2,l,mid,al,ar,v);
	if (ar>mid) _add(u*2+1,mid+1,r,al,ar,v);
	tree[u].Max=max(tree[u*2].Max,tree[u*2+1].Max);
	return ;
}
Tnode _ask() {return tree[1];}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d", &s[i].l, &s[i].r);
		p[++fp] = s[i].l;
		p[++fp] = s[i].r;
	}
	
	sort(p+1,p+fp+1);
	fp=unique(p+1,p+fp+1)-p-1;
	sort(s+1,s+n+1,_cmp);
	for (int i=1;i<=n;i++)
		s[i].l=pos(s[i].l),
		s[i].r=pos(s[i].r);
	
	for (int l=1,r=1;r<=n;r++)
	{
		_add(1,1,fp,s[r].l,s[r].r,1);
		for (;_ask().Max>=m;l++)
		{
			ans=min(ans,(p[s[r].r]-p[s[r].l])-(p[s[l].r]-p[s[l].l]));
			_add(1,1,fp,s[r].l,s[l].r,-1);
		}
	}
	printf("%d",ans==INF?-1:ans);
	return 0;
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100006,
		  MAXM = MAXN,
		  INF  = 1000000009;

struct Tbuild {int b,p;};
struct Tnode {int i,v;};

int n,m,ans,k=1,j;
long long tot;
int a[MAXN];
Tnode tree[MAXN*4];
Tbuild bing[MAXM];

Tnode min(Tnode a,Tnode b) {return (a.v<b.v)?a:b;}

void _build(int root,int l,int r)
{
	if (l==r)
	{
		tree[root].v=INF;
		tree[root].i=l;
		return ;
	}
	int mid=(l+r)/2;
	_build(root*2,l,mid);
	_build(root*2+1,mid+1,r);
	tree[root]=min(tree[root*2],tree[root*2+1]);
	return ;
}

void _update(int root,int l,int r,int pos,int v)
{
	if (l==r) 
	{
		tree[root].v=v;
		return ;
	}
	int mid=(l+r)/2;
	if (pos<=mid) _update(root*2,l,mid,pos,v);
		else _update(root*2+1,mid+1,r,pos,v);
	tree[root]=min(tree[root*2],tree[root*2+1]);
	return ;
}

Tnode _ask() {return tree[1];}
void _delete() {_update(1,1,m,_ask().i,INF);}
bool _cmp(Tbuild a,Tbuild b) {return (a.b==b.b)?a.p<b.p:a.b<b.b;}

int main()
{
	freopen("2353.in","r",stdin);
	freopen("2353.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++) scanf("%d",&bing[i].b);
	for (int i=1;i<=m;i++) scanf("%d",&bing[i].p);
	sort(bing+1,bing+1+m,_cmp);
	_build(1,1,m);
	for (int i=n;i>0;i=j)
	{
		tot=0ll;
	//	tot=a[i];
		for (j=i;j>0 && a[j]<=a[i];j--) tot=tot+(long long)a[j];
		
		for (;k<=m && bing[k].b<=a[i];k++)
			_update(1,1,m,k,bing[k].p);
		while (_ask().v!=INF)
		{
			if (tot>=_ask().v)
				ans++,tot-=(long long)_ask().v,_delete();
			else
			{
				tot=(int)_ask().v-tot;
				_update(1,1,m,_ask().i,(int)tot);
				break;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

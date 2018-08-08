#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = 2000009;

struct Tnode {int val,i;};

int v[MAXN*2],nxt[MAXN*2],head[MAXN],cnt;
int dfnl[MAXN],dfnr[MAXN],idfn[MAXN],dfn;
int lc[MAXM],rc[MAXM],tot[MAXM],root[MAXN],fp;
Tnode a[MAXN],b[MAXN];
int n;

bool cmpv(Tnode x,Tnode y) {return x.val<y.val;}
bool cmpi(Tnode x,Tnode y) {return x.i<y.i;}

void _connect(int x,int y) {v[++cnt]=y,nxt[cnt]=head[x],head[x]=cnt;}

void dfs(int x,int y)
{
	dfnl[x]=++dfn;
	idfn[dfn]=x;
	for (int i=head[x];i;i=nxt[i])
		if (v[i]!=y)
		{
			dfs(v[i],x);
		}
	dfnr[x]=dfn;
}

int build(int l,int r)
{
	int now=++fp;
	if (l==r) return now;
	int mid=l+r>>1;
	lc[now]=build(l,mid);
	rc[now]=build(mid+1,r);
	return now;
}

void up(int x)
{
	tot[x]=tot[lc[x]]+tot[rc[x]];
}

int add(int x,int l,int r,int val)
{
	int now=++fp;
	tot[now]=tot[x];
	lc[now]=lc[x];
	rc[now]=rc[x];
	if (val==l&&val==r)
	{
		tot[now]++;
		return now;
	}
	int mid=l+r>>1;
	if (val<=mid) lc[now]=add(lc[x],l,mid,val);
	if (val> mid) rc[now]=add(rc[x],mid+1,r,val);
	up(now);
	return now;
}

int query(int x,int y,int l,int r,int ql,int qr)
{
	if (ql<=l&&r<=qr)
	{
		return tot[x]-tot[y];
	}
	int mid=l+r>>1,ret=0; 
	if (ql<=mid) ret+=query(lc[x],lc[y],l,mid,ql,qr);
	if (qr> mid) ret+=query(rc[x],rc[y],mid+1,r,ql,qr);
	return ret;
}

int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);

	int x,y;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i].val),a[i].i=i;
	sort(a+1,a+1+n,cmpv);
	
	int num=1;
	b[1].val=1,b[1].i=a[1].i;
	for (int i=2;i<=n;i++)
	{
		if (a[i].val!=a[i-1].val) ++num;
		b[i].val=num;
		b[i].i=a[i].i;
	}

	root[0]=build(1,num);
	
	for (int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
		_connect(y,x);
	}
	
	dfs(1,0);
	sort(b+1,b+1+n,cmpi);
	
	for (int i=1;i<=n;i++)
	{
		int x=idfn[i];
		root[i]=add(root[i-1],1,num,b[x].val);
	}
	
	for (int i=1;i<=n;i++)
	{
		if (b[i].val==1) printf("1 ");
			else
			{
				int pri=query(root[dfnr[i]],root[dfnl[i]-1],1,num,1,b[i].val-1)+1;
				printf("%d ",pri);
			}
	}
	putchar('\n');

	return 0;
}



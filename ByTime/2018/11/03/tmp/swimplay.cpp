#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int mx=1e5+10;
int n,m;
int a[mx];
struct Tq
{
	int opt,l,r;
};
Tq q[mx];
int k;

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

void _init()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=0;i<m;i++)
		q[i].opt=read(),q[i].l=read(),q[i].r=read();
	k=read();
	
}

struct Tnode
{
	int l,r,lc,rc,num,fl;
	Tnode()
	{ l=r=lc=rc=num=fl=0; }
};
Tnode node[mx*2];
int fp=1;
int b[mx];

int build(int l,int r)
{
	if(l>r) return 0;
	int x=fp++;
	Tnode &t=node[x];
	t.l=l,t.r=r;
	if(l==r)
	{
		t.num=b[l];
		return x;
	}
	int mid=(l+r)>>1;
	t.lc=build(l,mid);
	t.rc=build(mid+1,r);
	t.num=node[t.lc].num+node[t.rc].num;
	return x;
}

void down(int x)
{
	if(!x) return ;
	Tnode &t=node[x];
	if(t.fl==0) return ;
	if(t.fl==1)
	{
		if(t.lc) node[t.lc].fl=1,node[t.lc].num=node[t.lc].r-node[t.lc].l+1;
		if(t.rc) node[t.rc].fl=1,node[t.rc].num=node[t.rc].r-node[t.rc].l+1;
	}
	if(t.fl==-1)
	{
		if(t.lc) node[t.lc].fl=-1,node[t.lc].num=0;
		if(t.rc) node[t.rc].fl=-1,node[t.rc].num=0;
	}	
	t.fl=0;
}

void insert(int x,int l,int r,int v)
{
	if(!x) return ;
	if(l>r) return ;
	down(x);
	Tnode &t=node[x];
	if(t.l==l && t.r==r)
	{
		t.fl=v;
		if(v==1) t.num=t.r-t.l+1;
		else t.num=0;
		return ;
	}
	int mid=(t.l+t.r)>>1;
	if(t.lc && l<=mid) insert(t.lc,l,min(mid,r),v);
	if(t.rc && r>mid) insert(t.rc,max(l,mid+1),r,v);
	
	
	t.num=node[t.lc].num+node[t.rc].num;
//	cerr<<l<<" "<<r<<": "<<t.l<<" "<<t.r<<" "<<node[t.rc].num<<endl;
}

int ask(int x,int l,int r)
{
	if(!x) return 0;
	if(l>r) return 0;
	down(x);
	Tnode &t=node[x];
	if(t.l==l && t.r==r)
		return t.num;
	int mid=(t.l+t.r)>>1;
	int ans=0;
	if(t.lc && l<=mid) ans+=ask(t.lc,l,min(mid,r));
	if(t.rc && r>mid) ans+=ask(t.rc,max(l,mid+1),r);
	return ans;	
}

bool calc(int p)
{
	memset(node,0,sizeof node);
	for(int i=1;i<=n;i++)
		if(a[i]>=p) b[i]=1;
		else b[i]=0;
	fp=1;
	build(1,n);
	
//	cerr<<p<<": "<<endl;
//	cerr<<ask(1,1,n)<<endl;
	
/*	insert(1,4,5,1);
	for(int j=1;j<=n;j++)
		cerr<<ask(1,j,j)<<" ";
	cerr<<endl;
	
	exit(0);
*/	
	int opt,l,r;
	for(int i=0;i<m;i++)
	{
		opt=q[i].opt,l=q[i].l,r=q[i].r;
		int cnt=ask(1,l,r);
//		cerr<<opt<<" "<<l<<" "<<r<<": "<<cnt<<endl;
		if(!opt) insert(1,l,r-cnt,-1),insert(1,r-cnt+1,r,1);
		else insert(1,l,l+cnt-1,1),insert(1,l+cnt,r,-1);
		
/*		for(int j=1;j<=n;j++)
			cerr<<ask(1,j,j)<<" ";
		cerr<<endl;
//		cerr<<ask(1,l,r)<<endl;
*/
	}
//	cerr<<"\n===============\n";
	int t=ask(1,k,k);
	return t;
}

void solve()
{
	int l=1,r=n+1,mid;
	while(l+1<r)
	{
		mid=(l+r)>>1;
		if(calc(mid)) l=mid;
		else r=mid;
	}
	printf("%d\n",l);
}

int main()
{
	freopen("swimplay.in","r",stdin);
	freopen("swimplay.out","w",stdout);

	_init();
	solve();
	
	
	
	return 0;
}

// Date      : 2018-12-26 18:13:02
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::max;
using std::min;
using std::swap;
using std::cerr;

const int MAXN = 100009,
		  MAXK = 109;

struct SegmentTree
{
	struct Tnode
	{
		int lc,rc,v;
		void clear() {lc=rc=v=0;}
		Tnode(){clear();}
	};
	Tnode t[MAXN*46];
	int Stack[MAXN*20];
	int root[MAXN];
	int fp,top;
	SegmentTree(){fp=1;top=0;}
	inline int _new() {return top?Stack[--top]:fp++;}
	inline void _free(int u)
	{
		t[u].clear();
		if (top==MAXN*20)
			return ;
		Stack[top++]=u;
		return ;
	}
	void init(int n,int m)
	{
		for (int i=1;i<=n;i++)
			root[i]=_new(),t[root[i]].v=m;
		return ;
	}
	void release(int u)
	{
		if (!u)
			return ;
		release(t[u].lc);
		release(t[u].rc);
		_free(u);
	}
	int modify(int& u,int l,int r,int al,int ar)
	{
		if (!u)
		{
			u=_new();
			t[u].v=r-l+1;
		}
		if (!t[u].v)
		{
			release(t[u].lc);
			release(t[u].rc);
			t[u].clear();
			return 0;
		}
		int sum=0;
		if (al<=l && ar>=r)
		{
			sum=t[u].v;
			t[u].v-=sum;
			return sum;
		}
		int mid=(l+r)>>1;
		if (al<=mid)
			sum+=modify(t[u].lc,l,mid,al,ar);
		if (ar>mid)
			sum+=modify(t[u].rc,mid+1,r,al,ar);
		t[u].v=0;
		if (t[u].lc)
			t[u].v+=t[t[u].lc].v;
		else
			t[u].v+=mid-l+1;
		if (t[u].rc)
			t[u].v+=t[t[u].rc].v;
		else
			t[u].v+=r-mid;
		return sum;
	}
};

SegmentTree ST;

int n,m,k;
int x[MAXK],y[MAXK],r[MAXK];
long long left,ans=0,sum;

int getlen(int a,int b)
{
	int l=0,r=m+1,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (1ll*mid*mid+1ll*b*b<=a*a)
			l=mid;
		else
			r=mid;
	}
	return l;
}

inline int read()
{
	char c;
	int x=0;
	do {c=getchar();}
		while (c<48 || c>57);
	do {x=x*10+c-48,c=getchar();}
		while (c>=48 && c<=57);
	return x;
}

int main()
{
	freopen("2741.in","r",stdin);
	freopen("2741.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	ST.init(n,m);
	for (int i=1;i<=k;i++)
		scanf("%d%d%d",&x[i],&y[i],&r[i]);
	left=1ll*n*m;
	int len;
	for (int i=k;i;i--)
	{
		sum=ST.modify(ST.root[x[i]],1,m,max(1,y[i]-r[i]),min(m,y[i]+r[i]));
		for (int j=1;j<=r[i];j++)
		{
			len=getlen(r[i],j);
			if (x[i]+j<=n)
				sum+=ST.modify(ST.root[x[i]+j],1,m,max(1,y[i]-len),min(y[i]+len,m));
			if (x[i]-j>0)
				sum+=ST.modify(ST.root[x[i]-j],1,m,max(1,y[i]-len),min(y[i]+len,m));
		}
		left-=sum;
		ans+=left;
	}
	printf("%lld\n",ans);
	return 0;
}
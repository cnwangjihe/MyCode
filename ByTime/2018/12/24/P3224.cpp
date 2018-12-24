// Date    : 2018-12-24 08:49:07
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 200000;

class SegmentTree
{
private:
	class Tnode
	{
	public:
		int lc,rc,c;
		void clear(){lc=rc=c=0;}
		Tnode(){clear();}
	};
	
	Tnode t[MAXN*30];
	int stack[MAXN*30];
	int top,fp;
	
	inline int _new() {return top?stack[--top]:fp++;}
	inline void _free(int u) {stack[top++]=u,t[u].clear();}
	inline void _up(int u) {t[u].c=t[t[u].lc].c+t[t[u].rc].c;}
public:
	SegmentTree(){top=0,fp=1;}
	int insert(int u,int l,int r,int v)
	{
		if (!u)
			u=_new();
		if (l==r)
			return t[u].c++,u;
		int mid=(l+r)>>1;
		if (v<=mid)
			t[u].lc=insert(t[u].lc,l,mid,v);
		else
			t[u].rc=insert(t[u].rc,mid+1,r,v);
		_up(u);
		return u;
	}
	int merge(int u1,int u2,int l,int r)
	{
		if (!u1)
			return u2;
		if (!u2)
			return u1;
		t[u1].c+=t[u2].c;
		int mid=(l+r)>>1;
		if (l!=r)
		{
			t[u1].lc=merge(t[u1].lc,t[u2].lc,l,mid);
			t[u1].rc=merge(t[u1].rc,t[u2].rc,mid+1,r);
		}
		_free(u2);
		return u1;
	}
	int query(int u,int l,int r,int k)
	{
		if (!u)
			return 0;
		if (l==r)
			return l;
		int mid=(l+r)>>1;
		if (t[u].lc && t[t[u].lc].c>=k)
			return query(t[u].lc,l,mid,k);
		else
			return query(t[u].rc,mid+1,r,k-t[t[u].lc].c);
	}
};

class UFset
{
private:
	SegmentTree ST;
	int fa[MAXN],root[MAXN];
	int n;
	int find(int u)
	{
		int x=u,t;
		while (u!=fa[u])
			u=fa[u];
		while (x!=fa[x])
		{
			t=fa[x];
			fa[x]=u;
			x=t;
		}
		return u;
	}
public:
	void init(int nn)
	{
		this->n=nn;
		for (int i=0;i<=nn;i++)
			fa[i]=i;
		return ;
	}
	UFset() {}
	void build(int v[])
	{
		for (int i=1;i<=n;i++)
			root[i]=ST.insert(0,1,n,v[i]);
		return ;
	}
	void merge(int x,int y)
	{
		int fx=find(x),fy=find(y);
		if (fx==fy)
			return ;
		fa[fy]=fx;
		ST.merge(root[fx],root[fy],1,n);
		return ;
	}
	inline int query(int x,int k){return ST.query(root[find(x)],1,n,k);}
};

UFset U;
int v[MAXN],pos[MAXN];
int n,m,q;

int main()
{
//	freopen("P3224.in","r",stdin);
//	freopen("P3224.out","w",stdout);
	int x,y;
	char c;
	scanf("%d%d",&n,&m);
	U.init(n);
	for (int i=1;i<=n;i++)
		scanf("%d",&v[i]),pos[v[i]]=i;
	pos[0]=-1;
	U.build(v);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		U.merge(x,y);
	}
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		do {c=getchar();}
			while (c!='B' && c!='Q');
		scanf("%d%d",&x,&y);
		if (c=='B')
			U.merge(x,y);
		else
			printf("%d\n",pos[U.query(x,y)]);
	}
	return 0;
}
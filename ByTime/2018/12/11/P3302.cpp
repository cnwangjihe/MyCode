// Date    : 2018-12-11 19:18:14
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 80009,
		  MAXC = 4000000,
		  MAXK = 20,
		  MAXV = 1000000009;

struct Tnode
{
	int lc,rc,c;
	void clear(){lc=rc=c=0;}
	Tnode(){clear();}
};

Tnode t[MAXC];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
int a[MAXN],deep[MAXN];
int jump[MAXN][MAXK];
int root[MAXN],rt[MAXN],size[MAXN];
int _stack[MAXC];
bool _in[MAXC];
int n,m,q,fp=0,top=0,ans=0;

void _init()
{
	for (int i=MAXC-1;i;i--)
		_stack[top++]=i,_in[i]=1;
}

inline int _new() {return _in[_stack[--top]]=0,_stack[top];}

inline void _free(int u) {_in[u]=1,t[_stack[top++]=u].clear();}

inline int _copy(int u,int v) {return t[v]=t[u],v;}

inline int _getsize(int u) {return size[root[u]];}

inline void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

int _modify(int u,int l,int r,int w)
{
	if (!u)
		u=_new();
	else
		u=_copy(u,_new());
	if (l==r)
	{
		t[u].c++;
		return u;
	}
	int mid=(l+r)>>1;
	if (w<=mid)
		t[u].lc=_modify(t[u].lc,l,mid,w);
	else
		t[u].rc=_modify(t[u].rc,mid+1,r,w);
	t[u].c=t[t[u].lc].c+t[t[u].rc].c;
//	cerr << "@@@ : " << l << " , " << r << " , " << t[u].c << " " << t[u].lc << " ' " << t[u].rc << '\n';
	return u;
}

int _query(int ufa1,int ufa2,int ua,int ub,int l,int r,int w)
{
	if (l==r)
		return l;
	int mid=(l+r)>>1,lcnt=t[t[ua].lc].c+t[t[ub].lc].c-t[t[ufa1].lc].c-t[t[ufa2].lc].c;
	if (lcnt>=w)
		return _query(t[ufa1].lc,t[ufa2].lc,t[ua].lc,t[ub].lc,l,mid,w);
	else
		return _query(t[ufa1].rc,t[ufa2].rc,t[ua].rc,t[ub].rc,mid+1,r,w-lcnt);	
}

void _release(int u,int l,int r)
{
	if (!u || _in[u])
		return ;
	if (l==r)
	{
		_free(u);
		return ;
	}
	int mid=(l+r)>>1;
	_release(t[u].lc,l,mid);
	_release(t[u].rc,mid+1,r);
	_free(u);
	return ;
}

void _delete(int u,int fa)
{
	int v;
	_release(rt[u],1,MAXV);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		_delete(v,u);
	}
	return ;
}

void _merge(int u,int fa)
{
	int v;
	root[u]=root[fa];
//	cerr << "~~~ : f**k\n";
	rt[u]=_modify(rt[fa],1,MAXV,a[u]);
//	cerr << "$$$ : " << u << "|" << fa << "|" << t[rt[u]].c << endl;
	jump[u][0]=fa;
	deep[u]=deep[fa]+1;
	for (int i=0;i<MAXK-1;i++)
		jump[u][i+1]=jump[jump[u][i]][i];
//	cerr << "``` : f**k\n";
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		_merge(v,u);
	}
	return ;
}

void _link(int a,int b)
{

	if (_getsize(a)>_getsize(b))
		swap(a,b);
//	cerr << "*** : " << a << ',' << b << '\n';
//	cerr << "^^^ : " << _getsize(a) << ',' << _getsize(b) << '\n';
//	cerr << "%%% : " << root[a] << ',' << root[b] << '\n';
	size[root[b]]+=size[root[a]];
	size[root[a]]=0;
	_connect(a,b);
	_connect(b,a);
	_delete(a,b);
//	cerr << "??? : " << top << "\n";
	_merge(a,b);
	return ;
}

int _getLCA(int a,int b)
{
	if (deep[a]<deep[b])
		swap(a,b);
	for (int i=MAXK-1;deep[a]!=deep[b];i--)
		if (deep[jump[a][i]]>=deep[b])
			a=jump[a][i];
	if (a==b)
		return a;
	for (int i=MAXK-1;jump[a][0]!=jump[b][0];i--)
		if (jump[a][i]!=jump[b][i])
			a=jump[a][i],b=jump[b][i];
	return jump[a][0];
}

inline int _ask(int x,int y,int w)
{
	int LCA = _getLCA(x,y);
	return _query(rt[jump[LCA][0]],rt[LCA],rt[x],rt[y],1,MAXV,w);
}

int main()
{
//	freopen("P3302.in","r",stdin);
//	freopen("P3302.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,w,casenum,type;
	char c;
	_init();
	scanf("%d",&casenum);
	scanf("%d%d%d",&n,&m,&q);

	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]++;
		rt[i]=_modify(0,1,MAXV,a[i]);
		root[i]=i;
		size[i]=1;
		deep[i]=1;
//		cerr << "### : " <<  t[rt[i]].c << '\n';
	}
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		_link(x,y);
	}
//	cerr << t[rt[8]].c << endl;
	for (int i=0;i<q;i++)
	{
		do {c=getchar();}
			while (c!='Q' && c!='L');
		type=(c=='Q');
		if (type)
		{
			scanf("%d%d%d",&x,&y,&w);
			x^=ans,y^=ans,w^=ans;
			printf("%d\n",ans=_ask(x,y,w)-1);
		}
		else
		{
			scanf("%d%d",&x,&y);
			x^=ans,y^=ans;
			_link(x,y);
		}
	}
	return 0;
}
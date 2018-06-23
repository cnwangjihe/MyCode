#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  INF  = 2147483647;

struct Tnode{int v,c;};

Tnode t[MAXN*4];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
int size[MAXN],son[MAXN],deep[MAXN],top[MAXN];
int w[MAXN],rw[MAXN],fa[MAXN];
int jump[MAXN][20];
int val[MAXN];
int n,m,fp=0,tim=0,root;

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0')
	{
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x *= 10;
		x += (ch - '0');
		ch = getchar();
	}
	return x * f;
}

inline void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

inline void _up(int u)
{
	t[u].v=min(t[u*2].v,t[u*2+1].v);
	return ;
}

inline void _down(int u)
{
	if (t[u].c==-1)
		return ;
	t[u*2].c=t[u*2+1].c=t[u].c;
	t[u*2].v=t[u*2+1].v=t[u].c;
	t[u].c=-1;
	return ;
}

void _build(int u,int l,int r)
{
	t[u].c=-1;
	if (l==r)
	{
		t[u].v=(val[rw[l]]==-1)?INF:val[rw[l]];
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	_up(u);
}

void _modify(int u,int l,int r,int al,int ar,int v)
{
	if (al<=l && ar>=r)
	{
		t[u].c=t[u].v=v;
		return ;
	}
	_down(u);
	int mid=(l+r)/2;
	if (al<=mid)
		_modify(u*2,l,mid,al,ar,v);
	if (ar>mid)
		_modify(u*2+1,mid+1,r,al,ar,v);
	_up(u);
	return ;
}

int _query(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u].v;
	_down(u);
	int mid=(l+r)/2,ans=INF;
	if (al<=mid)
		ans=min(ans,_query(u*2,l,mid,al,ar));
	if (ar>mid)
		ans=min(ans,_query(u*2+1,mid+1,r,al,ar));
	return ans;
}

void dfs1(int u)
{
	int v;
	jump[u][0]=fa[u];
	for (int i=1;jump[u][i-1];i++)
		jump[u][i]=jump[jump[u][i-1]][i-1];
	size[u]=1,son[u]=0;
	deep[u]=deep[fa[u]]+1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u])
			continue;
		fa[v]=u;
		dfs1(v);
		size[u]+=size[v];
		if (size[son[u]]<size[v])
			son[u]=v;
	}
	return ;
}

void dfs2(int u)
{
//	cerr << u << ' ' << top[u] << '\n';
	int v;
	w[u]=++tim;
	rw[w[u]]=u;
	if (!son[u])
		return ;
	top[son[u]]=top[u];
	dfs2(son[u]);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa[u] || v==son[u])
			continue;
		top[v]=v;
		dfs2(v);
	}
	return ;
}

int _jump(int u,int k)
{
	for (int i=0;k;i++)
		if (k&(1<<i))
			k-=(1<<i),u=jump[u][i];
	return u;
}

int LCA(int u,int v)
{
	if (deep[u]<deep[v])
		swap(u,v);
	u=_jump(u,deep[u]-deep[v]);
	if (u==v)
		return u;
	for (int i=18;~i;i--)
		if (jump[u][i]!=jump[v][i])
			u=jump[u][i],v=jump[v][i];
//	cerr << fa[u] << "asd" << endl;
	return fa[u];
}

void modify(int x,int y,int v)
{
	while (top[x]!=top[y])
	{
		if (deep[top[x]]<deep[top[y]])
			swap(x,y);
		_modify(1,1,n,w[top[x]],w[x],v);
		x=fa[top[x]];
	}
	if (deep[x]>deep[y])
		swap(x, y);
	_modify(1,1,n,w[x],w[y],v);
	return ;
}

int main()
{
	memset(_head,-1,sizeof _head);
	memset(val,-1,sizeof val);
	int t,a,b,c;
	n=read(),m=read();
	for (int i=1;i<n;i++)
	{
		a=read(),b=read();
		_connect(a,b);
		_connect(b,a);
	}
	for (int i=1;i<=n;i++)
		val[i]=read();
	root=read();
	top[1]=1;
	dfs1(1);
	dfs2(1);
	_build(1,1,n);
	for (int i=0;i<m;i++)
	{
		t=read();
		if (t==1)
			root=read();
		if (t==2)
		{
			a=read(),b=read(),c=read();
			modify(a,b,c);
		}
		if (t==3)
		{
			a=read();
			if (a==root)
				printf("%d\n",_query(1,1,n,1,n));
			else if(LCA(a,root)==a)
			{
				b=_jump(root,deep[root]-deep[a]-1);
//				cerr << b << endl;
				printf("%d\n", min(_query(1,1,n,1,w[b]-1),_query(1,1,n,w[b]+size[b],n)));
			}
			else 
				printf("%d\n",_query(1,1,n,w[a],w[a]+size[a]-1));
		}
	}
	return 0;
}
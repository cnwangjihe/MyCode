/*
#include <bits/stdc++.h>

using namespace std;

struct Tnode{int v,a,c;};

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
	t[u].v=t[u*2].v+t[u*2+1].v;
	return ;
}

inline void _down(int u)
{
	if (t[u].a==0)
		return ;
	t[u*2].a=t[u*2+1].a=1;
	t[u*2].v=t[u*2].c;
	t[u*2+1].v=t[v*2+1].c;
	t[u].a=0;
	return ;
}

void _build(int u,int l,int r)
{
	if (l==r)
	{
		t[u].v=0;
		t[u].c=1;
		t[u].a=0;
		return ;
	}
	int mid=(l+r)/2;
	_build(u*2,l,mid);
	_build(u*2+1,mid+1,r);
	t[u].c=t[u*2].c+t[u*2+1].c;
	_up(u);
	return ;
}

void _modify(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
	{
		t[u].a=1;
		t[u].v=t[u].c;
		return ;
	}
	_down(u);
	int mid=(l+r)/2;
	if (al<=mid)
		_modify(u*2,l,mid,al,ar);
	if (ar>mid)
		_modify(u*2+1,mid+1,r,al,ar);
	_up(u);
	return ;
}

int _query(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u].v;
	_down(u);
	int mid=(l+r)/2,ans=0;
	if (al<=mid)
		ans+=_query(u*2,l,mid,al,ar);
	if (ar>mid)
		ans+=_query(u*2+1,mid+1,r,al,ar);
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
	return fa[u];
}

void modify(int x,int y)
{
	while (top[x]!=top[y])
	{
		if (deep[top[x]]<deep[top[y]])
			swap(x,y);
		_modify(1,1,n,w[top[x]],w[x]);
		x=fa[top[x]];
	}
	if (deep[x]>deep[y])
		swap(x,y);
	_modify(1,1,n,w[x],w[y]);
	return ;
}

int query(int x,int y)
{
	int ans=0;
	while (top[x]!=top[y])
	{
		if (deep[top[x]]<deep[top[y]])
			swap(x,y);
		ans+=_query(1,1,n,w[top[x]],w[x]);
		x=fa[top[x]];
	}
	if (deep[x]>deep[y])
		swap(x,y);
	ans+=_query(1,1,n,w[x],w[y]);
	return ans;
}

int main()
{
	n=read();
	sum=(1ll*n*(1ll*n+1ll))/2ll;
	for (int i=1;i<=n;i++)
	{
		col[i]=read();
		p[col[i]].push_back(i);
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<p[i].size();j++)
		{

		}
	}
}
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
int _in[MAXN],col[MAXN];
long long ans=0;
int n,fp=0;

inline void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

inline int read()
{
	int tmp=0,w=1;
	char ch=0;
	while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0' && ch<='9') tmp=(tmp<<1)+(tmp<<3)+ch-'0',ch=getchar();
	return tmp*w;
}

void dfs(int u,int fa)
{
	if (_in[col[u]])
		return;
	ans++;
	_in[col[u]]=1;
	for (int i=_head[u];~i;i=_next[i])
		if (_node[i]!=fa)
			dfs(_node[i],u);
	_in[col[u]]--;
	return ;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	n=read();
	memset(_head,-1,sizeof _head);
	for (int i=1;i<=n;i++)
		col[i]=read();
	int x,y;
	for (int i=1;i<n;i++)
	{
		x=read();y=read();
		_connect(x,y);
		_connect(y,x);
	}
	if (n<=3000)
	{
		for (int i=1;i<=n;i++)
			dfs(i,0);
		printf("%lld\n",(ans-n)/2+n);
		return 0;
	}
	else 
	{
		int t=1;
		_in[col[1]]=1;
		for (int i=1;i<=n;i++)
		{
			while (t<n && _in[col[t+1]]==0)
				_in[col[++t]]++;
			ans+=t-i+1;
			_in[col[i]]--;
		}
		printf("%lld\n",ans);
		return 0;
	}
}
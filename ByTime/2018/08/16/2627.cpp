#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300009,
		  MOD  = 1000000007;

struct Tnode
{
	bool v[2];
	int c;
	Tnode (bool a1=0,bool a2=0){v[0]=a1,v[1]=a2,c=-1;}
	Tnode operator+(const Tnode& a)
	{
		Tnode ans=*this;
		ans.v[0]|=a.v[0];
		ans.v[1]|=a.v[1];
		ans.c=-1;
		return ans;
	}
	Tnode operator+=(const Tnode& a)
	{
		*this=*this+a;
		return *this;
	}
};

Tnode t[MAXN*4];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2];
int size[MAXN],son[MAXN],deep[MAXN],top[MAXN];
int w[MAXN],fa[MAXN];
int jump[MAXN][20];
int a[MAXN],b[MAXN];
int fp=0,tim=0;
int n,m,ans=0;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

inline void _up(int u)
{
	t[u]=t[u*2]+t[u*2+1];
	return ;
}

inline void _down(int u)
{
	if (t[u].c==-1)
		return ;
	t[u*2].v[t[u].c]=t[u*2+1].v[t[u].c]=1;
	t[u*2].v[!t[u].c]=t[u*2+1].v[!t[u].c]=0;
	t[u*2].c=t[u*2+1].c=t[u].c;
	t[u].c=-1;
	return ;
}

void _modify(int u,int l,int r,int al,int ar,bool v)
{
	if (al<=l && ar>=r)
	{
		t[u].c=v;
		t[u].v[v]=1;
		t[u].v[!v]=0;
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

Tnode _query(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u];
	_down(u);
	int mid=(l+r)/2;
	Tnode ans;
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
//	cerr << u << ' ' << top[u] << '\n';
	int v;
	w[u]=++tim;
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
	for (int i=19;~i;i--)
		if (jump[u][i]!=jump[v][i])
			u=jump[u][i],v=jump[v][i];
	return fa[u];
}

void modify(int x,int y,bool v)
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
	_modify(1,1,n,w[x]+1,w[y],v);
	return ;
}

Tnode query(int x,int y)
{
	Tnode ans;
	while (top[x]!=top[y])
	{
		if (deep[top[x]]<deep[top[y]])
			swap(x,y);
		ans+=_query(1,1,n,w[top[x]],w[x]);
		x=fa[top[x]];
	}
	if (deep[x]>deep[y])
		swap(x, y);
	ans+=_query(1,1,n,w[x]+1,w[y]);
	return ans;
}

/*
void bfs()
{
	int head=0,tail=0;
	line[tail++]=1;
	_in[1]=1;
	while (head!=tail)
	{
		u=line[head++];

	}
}
*/

inline int getcolor(Tnode a)
{
	return (a.v[0] && a.v[1])?2:((!a.v[0] && !a.v[1])?-1:(a.v[0]?0:1));
}

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=(a*a)%MOD)
		if ((1<<i)&k)
			ans=(ans*a)%MOD;
	return ans;
}

int main()
{
	freopen("2627.in","r",stdin);
	freopen("2627.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,col1,col2,lca;
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
		_connect(y,x);
	}
	dfs1(1);
	dfs2(1);
	for (int i=0;i<m;i++)
		scanf("%d%d",&a[i],&b[i]);
	for (int i=0;i<m;i++)
	{
		lca=LCA(a[i],b[i]);
		if (lca==a[i] || lca==b[i])
		{
		//	cerr << a[i] << ' ' << b[i] << '\n';
			col1=getcolor(query(a[i],b[i]));
			if (col1==2)
				return printf("0\n"),0;
			if (col1==-1)
			{
				ans++;
				modify(a[i],b[i],0);
			}
			else
				modify(a[i],b[i],col1);
		}
		else
		{
			col1=getcolor(query(a[i],lca));
		//	cerr << "All right!\n";
			col2=getcolor(query(b[i],lca));
			if (col1==2 || col2==2 || (col1!=-1 && col1==col2))
				return printf("0\n"),0;
			if (col1+col2==-2)
			{
				ans++;
				modify(a[i],lca,0);
				modify(b[i],lca,1);
			}
			else
			{
				if (col1==-1)
					col1=!col2;
				if (col2==-1)
					col2=!col1;
				modify(a[i],lca,col1);
				modify(b[i],lca,col2);
			}
		}
	}
//	cerr << ans << endl;
	for (int i=2;i<=n;i++)
		if (getcolor(_query(1,1,n,w[i],w[i]))==-1)
			ans++;
	printf("%d\n",qpow(2,ans));
	return 0;
}
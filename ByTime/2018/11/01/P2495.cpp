#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2*250009,
		  MAXM = MAXN*2;
const long long INF = 100000000000000000ll;

int _head[MAXN],_next[MAXM],_node[MAXM];
long long _val[MAXM];
int dfn[MAXN],deep[MAXN];
long long dis[MAXN];
int jump[MAXN][22];
int p[MAXN];
int Stack[MAXN],value[MAXN];
int fp=0,tim=0,k,n,top,q,m;
map <int,int> id,mp;

void _connect(int a,int b,long long v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa)
{
	int v;
	dfn[u]=++tim;
	deep[u]=deep[fa]+1;
	jump[u][0]=fa;
	for (int i=0;jump[u][i];i++)
		jump[u][i+1]=jump[jump[u][i]][i];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dis[v]=min(dis[u],1ll*_val[i]);
		dfs(v,u);
	}
	return ;
}

int LCA(int a,int b)
{
	if (deep[a]<deep[b])
		swap(a,b);
	int h=deep[a]-deep[b];
	for (int i=0;h;h=(h|(1<<i))^(1<<i),i++)
		if (h&(1<<i))
			a=jump[a][i];
	if (a==b)
		return a;
	for (int i=20;(~i) && jump[a][0]!=jump[b][0];i--)
		if (jump[a][i]!=jump[b][i])
			a=jump[a][i],b=jump[b][i];
	return jump[a][0];
}

bool _cmp(int a,int b) {return dfn[a]<dfn[b];}

int Getid(int a)
{
	if (!id.count(a))
		id[a]=++k,mp[k]=a;
	return id[a];
}

void build(int p[],int m)
{
	sort(p+1,p+m+1,_cmp);
	int u,v,a,b;
	top=0;
	for (int i=1;i<=m;i++)
	{
		if (top)
		{
			u=Stack[top-1];
			v=LCA(u,p[i]);
			// cerr << "## " << u << ' ' << p[i] << ' ' << v << '\n';
			if (u!=v)
			{
				while (top-2>=0 && deep[Stack[top-2]]>=deep[v])
				{
					a=Stack[top-1],b=Stack[top-2];
					_connect(Getid(a),Getid(b),0);
					_connect(Getid(b),Getid(a),0);
					top--;
				}
				a=Stack[--top],b=v;
				if (v!=a)
				{
					_connect(Getid(a),Getid(b),0);
					_connect(Getid(b),Getid(a),0);
				}
				Stack[top++]=v;
			}
			Stack[top++]=p[i];
		}
		else
			Stack[top++]=p[i];
	}
	while (top-2>=0)
	{
		a=Stack[top-1],b=Stack[top-2];
		_connect(Getid(a),Getid(b),0);
		_connect(Getid(b),Getid(a),0);
		top--;
	}
	return ;
}

long long dfs2(int u,int fa)
{
	 // cerr << "f**k _in " << u << ' ' << mp[u]<< '\n';
	int v;
	long long sum=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		sum+=dfs2(v,u);
	}
	 // cerr << "f**k _out " << mp[u] << ' ' << dis[mp[u]] << ' ' << sum  <<  '\n' ;
	if (value[mp[u]])
		return 1ll*dis[mp[u]];
	return min(sum,1ll*dis[mp[u]]);
}

int main()
{
	memset(_head,-1,sizeof _head);
	int x,y,z;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	dis[1]=INF;
	dfs(1,0);
	int tfp=fp;
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf("%d",&m);
		p[1]=1;
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&p[j+1]);
			value[p[j+1]]=1;
		}
		k=n;
		id.clear(),mp.clear();
		build(p,m+1);
		// cerr << value[1] << "f**k\n";
		printf("%lld\n",dfs2(Getid(1),0));
		fp=tfp;
		for (int j=1;j<=m;j++)
			value[p[j+1]]=0;
		for (int j=n+1;j<=k;j++)
			_head[j]=-1;
	}
	return 0;
}
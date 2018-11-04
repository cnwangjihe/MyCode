#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = MAXN*2;
const long long INF = 10000000000000000ll;

struct Troute
{
	int id;
	long long sum,Min;
	Troute(int a=0,long long b=0,long long c=0):id(a),sum(b),Min(c){}
};

Troute r[MAXN];
int _head[MAXN],_next[MAXM],_node[MAXM];
long long _val[MAXM];
long long t[MAXN*4];
int s[MAXN],f[MAXN];
bool done[MAXN];
long long a[MAXN];
int fp=0,n,root,tp;
long long ans=0;

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

inline void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void _clean(int n)
{
	for (int i=1;i<4*n;i++)
		t[i]=0;
	return ;
}

void _modify(int u,int l,int r,int p,long long v)
{
	if (l>r)
		return ;
	if (l==r)
	{
		t[u]=max(t[u],v);
		return ;
	}
	int mid=(l+r)>>1;
	if (p<=mid)
		_modify(u*2,l,mid,p,v);
	else
		_modify(u*2+1,mid+1,r,p,v);
	t[u]=max(t[u*2],t[u*2+1]);
	return ;
}

long long _query(int u,int l,int r,int al,int ar)
{
	if (al>ar || l>r)
		return 0;
	if (al<=l && ar>=r)
		return t[u];
	int mid=(l+r)>>1;
	long long ans=0;
	if (al<=mid)
		ans=max(ans,_query(u*2,l,mid,al,ar));
	if (ar>mid)
		ans=max(ans,_query(u*2+1,mid+1,r,al,ar));
	return ans;
}

bool _cmp(Troute a,Troute b) {return a.Min>b.Min;}

void _getroot(int u,int fa,int sz)
{
	int v;
	s[u]=1,f[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v] || v==fa)
			continue;
		_getroot(v,u,sz);
		s[u]+=s[v];
		f[u]=max(f[u],s[v]);
	}
	f[u]=max(f[u],sz-s[u]);
	// cerr << "## " << u << ' ' << f[u] << endl;
	if (f[u]<f[root])
		root=u;
	// cerr << "** " << root << '\n';
	return ;
}

void calc(int u,int fa,long long sum,long long Min,int id)
{
	// cerr << "$$ " << id << " : " << u << endl;
	int v;
	Min=min(Min,a[u]);
	r[tp++]=Troute(id,sum,Min);
	s[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v] || v==fa)
			continue;
		calc(v,u,sum+_val[i],Min,id);
		s[u]+=s[v];
	}
	return ;
}

void _getans(int u,int n)
{
	sort(r,r+tp,_cmp);
	_modify(1,1,n,r[0].id,r[0].sum);
	for (int i=1;i<tp;i++)
	{
		ans=max(ans, min(a[u],r[i].Min)*(max(_query(1,1,n,1,r[i].id-1),_query(1,1,n,r[i].id+1,n))+r[i].sum) );
		_modify(1,1,n,r[i].id,r[i].sum);
	}
	return ;
}

void dfs(int u,int sz)
{
	root=0;
	_getroot(u,0,sz);
	u=root;
	int id=0,v;
	done[u]=1;tp=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v])
			continue;
		calc(v,u,_val[i],INF,++id);
	}
	// cerr << "root& : " << u << ' ' << sz << endl;
	r[tp++]=Troute(++id,0,INF);
	_clean(sz);
	_getans(u,sz);
	// cerr << ans << endl;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v])
			continue;
		dfs(v,s[v]);
	}
	return ;
}

int main()
{
	freopen("shadow.in","r",stdin);
	freopen("shadow.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		memset(_head,-1,sizeof _head);
		memset(done,0,sizeof done);
		fp=0;
		int x,y,z;
		n=read();
		for (int i=1;i<=n;i++)
			a[i]=read();
		for (int i=1;i<n;i++)
		{
			x=read(),y=read(),z=read();
			_connect(x,y,z);
			_connect(y,x,z);
		}
		ans=0;
		f[0]=10000000;
		dfs(1,n);
		printf("%lld\n",ans);
	}
	return 0;
}
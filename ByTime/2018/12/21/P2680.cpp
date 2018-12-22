// Date    : 2018-12-21 08:05:52
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

#define cerr std::cerr

const int MAXN = 300009,
		  MAXK = 23;

struct Troute{int a,b,v,lca;};

Troute r[MAXN];
int _head[MAXN],_node[MAXN*2],_next[MAXN*2],_val[MAXN*2];
int jmp[MAXN][MAXK],sum[MAXN][MAXK];
int dep[MAXN],tag[MAXN];
int n,m,fp=0,maxlen=0;

bool _cmp(Troute a,Troute b){return a.v>b.v;}

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa,int w)
{
	int v;
	jmp[u][0]=fa;
	sum[u][0]=w;
	dep[u]=dep[fa]+1;
	for (int i=0;i+1<MAXK && jmp[u][i];i++)
	{
		jmp[u][i+1]=jmp[jmp[u][i]][i];
		sum[u][i+1]=sum[u][i]+sum[jmp[u][i]][i];
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u,_val[i]);
	}
	return ;
}

std::pair<int,int> LCA(int a,int b)
{
	int ans=0;
	if (dep[a]<dep[b])
		std::swap(a,b);
	for (int i=MAXK-1;dep[a]!=dep[b] && ~i;i--)
		if (dep[jmp[a][i]]>=dep[b])
		{
			ans+=sum[a][i];
			a=jmp[a][i];
		}
	if (a==b)
		return std::make_pair(a,ans);
	for (int i=MAXK-1;jmp[a][0]!=jmp[b][0] && ~i;i--)
		if (jmp[a][i]!=jmp[b][i])
		{
			ans+=sum[a][i]+sum[b][i];
			a=jmp[a][i],b=jmp[b][i];
		}
	return std::make_pair(jmp[a][0],ans+sum[a][0]+sum[b][0]);
}

int count(int u,int fa,int k)
{
	int v,ans=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		ans=std::max(ans,count(v,u,k));
		tag[u]+=tag[v];
	}
	if (tag[u]==k)
		ans=std::max(ans,sum[u][0]);
	return ans;
}

bool check(int v)
{
	int cnt=0,maxlen=0;
	memset(tag,0,sizeof tag);
	for (int i=0;i<m && v<r[i].v;i++)
	{
		tag[r[i].a]++,tag[r[i].b]++;
		tag[r[i].lca]-=2;
		cnt++;
		maxlen=std::max(maxlen,r[i].v);
	}
//	cerr << v << ' ' << cnt << '\n';
	return (maxlen-count(1,0,cnt)<=v);
}

int main()
{
//	freopen("P2680.in","r",stdin);
//	freopen("P2680.out","w",stdout);
//	std::ofstream fcheck("my.out");
	memset(_head,-1,sizeof _head);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	dfs(1,0,0);
	std::pair<int,int> tmp;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		tmp=LCA(x,y);
		r[i].lca=tmp.first;
		r[i].v=tmp.second;
		r[i].a=x,r[i].b=y;
//		fcheck << "*** : " << r[i].lca << '\n';
	}
	std::sort(r,r+m,_cmp);
	int l=-1,r=300000002,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%d\n",r);
	return 0;
}
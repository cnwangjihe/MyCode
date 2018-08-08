#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100009,
		  MAXM = MAXN*2,
		  INF  = 1000000007;

int _node[MAXM],_head[MAXN],_next[MAXM];
int val[MAXN],Right[MAXN],Left[MAXN],mLeft[MAXN],mRight[MAXN];
int s[MAXN],f[MAXN],cnt[MAXN];
bool done[MAXN];
int n,fp=0,ans=0,root;

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void _getroot(int u,int fa,int size)
{
	int v;
	s[u]=1,f[u]=0;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa || done[v])
			continue;
		_getroot(v,u,size);
		s[u]+=s[v];
		f[u]=max(f[u],s[v]);
	}
	f[u]=max(f[u],size-s[u]);
	if (f[u]<f[root])
		root=u;
	return ;
}

void _getsiz(int u,int fa)
{
	int v;
	s[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa || done[v])
			continue;
		_getsiz(v,u);
		s[u]+=s[v];
	}
	return ;
}

void _getcnt(int u,int fa)
{
	int v;
	cnt[u]=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa || done[v])
			continue;
		_getcnt(v,u);
		cnt[u]=max(cnt[u],cnt[v]+1);
	}
	return ;
}

void _getLeft(int u,int fa,int cntr,int cntl,int Max)
{
	if (val[u]==1)
		if (cntr) cntr--; else cntl++;
	else cntr++;
//	if (u==7)
//		cerr << cntr << ' '<< cntl << endl;
	Max=max(val[u]+Max,0);
	if (!cntr)
		Left[cntl]=max(Left[cntl],Max);
	int v;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v] || v==fa)
			continue;
		_getLeft(v,u,cntr,cntl,Max);
	}
}

void _getRight(int u,int fa,int cntr,int cntl,int Max,int s)
{
	int v;
	if (val[u]==-1)
		if (cntl) cntl--; else cntr++;
	else cntl++;
//	if (u==7)
//		cerr << cntr << ' '<< cntl << endl;
	s+=val[u];
	Max=max(s,Max);
	if (!cntl)
		Right[cntr]=max(Right[cntr],Max);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v] || v==fa)
			continue;
		_getRight(v,u,cntr,cntl,Max,s);
	}
}

void dfs(int u,int size)
{
	int v;
	root=n+2;
	_getroot(u,0,size);
	u=root;
	_getsiz(u,0);
//	cerr << u << ":" << size << endl;
	done[u]=1;
	for (int i=0;i<=size;i++)
		mLeft[i]=mRight[i]=-INF;
	mRight[0]=0;
	int x=0,y=0;
	if (val[u]==1)
		mLeft[1]=1,y=1;
	else
		x=1;
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v])
			continue;
		_getcnt(v,u);
		cnt[v]+=2;
		for (int i=0;i<=cnt[v];i++)
			Left[i]=Right[i]=-INF;
		_getLeft(v,u,x,y,y);
		_getRight(v,u,0,0,0,0);
		for (int i=0;i<=cnt[v];i++)
		{
//			if (u==8)
//				cerr << Left[i] << ' '<< mLeft[i] << ' '<< Right[i] << ' '<< mRight[i] << '\n';
			if (mLeft[i]>=0 && Right[i]>=0)
				ans=max(ans, max(mLeft[i],i+Right[i]));
			if (Left[i]>=0 && mRight[i]>=0)
				ans=max(ans, max(Left[i],i+mRight[i]));
		}
//		cerr << '\n';
		for (int i=0;i<=cnt[v];i++)
			mLeft[i]=max(mLeft[i],Left[i]),
			mRight[i]=max(mRight[i],Right[i]);
	}
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v])
			continue;
	//	cerr << s[v] << endl;
		dfs(v,s[v]);
	}
	return ;
}

int main()
{
	freopen("2443.in","r",stdin);
	freopen("2443.out","w",stdout);
	int a,rt;
	while (scanf("%d",&n)==1 && n)
	{
		fp=0;
		memset(_head,-1,sizeof _head);
		memset(done,0,sizeof done);
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&a,&val[i]);
			if (a)
				_connect(i,a),_connect(a,i);
			else
				rt=i;
		}
		f[n+2]=n+2;
		ans=0;
		dfs(rt,n);
		printf("%d\n",ans);
	}
}
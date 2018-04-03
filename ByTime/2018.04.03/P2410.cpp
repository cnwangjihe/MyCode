#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAXN = 209,
		  MAXM = MAXN*MAXN,
		  INF  = 0x7fffffff;

int _head[MAXN],_cur[MAXN],_next[MAXM],_node[MAXM],_val[MAXM];
long long _cost[MAXM],dis[MAXN];
int fp=0,S,T,n,m;
bool _in[MAXN];
int line[MAXN];
int ans[MAXN][MAXN];

template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}

void _add(int a,int b,int v,long long c)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_cost[fp]=c;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b,int v,long long c)
{
	_add(a,b,v,c);
	_add(b,a,0,-c);
	return ;
}

bool SPFA()
{
	memset(_in,0,sizeof _in);
	memset(dis,0x7f,sizeof dis);
	int head=0,tail=0,u,v;
	line[tail++]=S;
	dis[S]=0,_in[S]=1;
	while (head!=tail)
	{
	//	cerr << u << endl;
		u=line[head++];
		head%=MAXN;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (_val[i] && dis[v]>dis[u]+_cost[i])
			{
				dis[v]=dis[u]+_cost[i];
				if (!_in[v])
					_in[v]=1,line[tail++]=v,tail%=MAXN;
			}
		}
		_in[u]=(u==T)?1:0;
	}
//	cerr << dis[T] << '\n';
	return _in[T];
}

int tmp;

int dfs(int u,int Min)
{
	if (u==T)
		return Min;
	_in[u]=1;
	int ans=0;
	for (int &i=_cur[u];~i;i=_next[i])
	{
		if (_in[_node[i]] || dis[u]+_cost[i]!=dis[_node[i]] || !_val[i])
			continue;
		tmp=dfs(_node[i],min(Min-ans,_val[i]));
		_val[i]-=tmp;
		_val[i^1]+=tmp;
		ans+=tmp;
		if (ans==Min)
			break;
	}
	_in[u]=0;
	return ans;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int p;
	double t;
	scanf("%d%d",&n,&m);
	S=0,T=n+m+1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			read(p);
			t=log2((double)p*10000000.0);
			t*=-10000000.0;
			_connect(i,j+n,1,(long long)t);
		}
	for (int i=1;i<=n;i++)
	{
		read(p);
		_connect(S,i,p,0);
	}
	for (int i=1;i<=m;i++)
	{
		read(p);
		_connect(i+n,T,p,0);
	}
	int tt;
	while (SPFA())
	{
		memcpy(_cur,_head,sizeof _head);
		memset(_in,0,sizeof _in);
		dfs(S,INF);
		tt++;
	//	if (tt>1000)
	//		t/=(t-t);
	}
	for (int i=1;i<=n;i++)
		for (int j=_head[i];~j;j=_next[j])
			if (!(j&1))
				ans[i][_node[j]-n]=(!_val[j]);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			putchar(ans[i][j]+'0');
		putchar('\n');
	}
	return 0;
}
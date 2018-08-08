#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 179,
		  MAXM = 100*100*20,
		  INF  = 0x7fffffff;

int _head[MAXN],_cur[MAXN],_next[MAXM],_node[MAXM],_val[MAXM],_val2[MAXM];
int _cost[MAXM],dis[MAXN];
int fp=0,S,T,n,m;
bool _in[MAXN],check[MAXM];
int line[MAXN];
int mp[MAXN][MAXN];

int _add(int a,int b,int v,int c)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_cost[fp]=c;
	return _head[a]=fp++;
}

int _connect(int a,int b,int v,int c)
{
	_add(b,a,0,-c);
	return _add(a,b,v,c);
}


bool SPFA()
{
	memset(_in,0,sizeof _in);
	fill(dis,dis+MAXN,-INF);
	int head=0,tail=0,u,v;
	line[tail++]=S;
	dis[S]=0,_in[S]=1;
	while (head!=tail)
	{
	//  cerr << u << endl;
		u=line[head++];
		head%=MAXN;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (_val[i] && dis[v]<dis[u]+_cost[i])
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

int dfs(int u,int Min)
{
	if (u==T)
		return Min;
	_in[u]=1;
	int ans=0,tmp;
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

int maxflow()
{
	int ans=0,tmp,sum=0;
	while (SPFA())
	{
		memcpy(_cur,_head,sizeof _head);
		memset(_in,0,sizeof _in);
		tmp=dfs(S,INF);
		ans+=tmp*dis[T];
		sum+=tmp;
	}
	return sum==n?ans:-1;
}

int main()
{
//	freopen("P3967.in","r",stdin);
//	freopen("P3967.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int c,ans;
	scanf("%d",&n);
	S=0,T=n*2+1;
	int tmp;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&c),
			mp[i][j]=_connect(i,j+n,1,c);
	for (int i=1;i<=n;i++)
		_connect(S,i,1,0),_connect(i+n,T,1,0);
	memcpy(_val2,_val,sizeof _val);
	ans=maxflow();
	printf("%d\n",ans);
    for (int i=0;i<fp;i++)
    	if(!_val[i])
    		check[i]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (!check[mp[i][j]])
				continue;
			memcpy(_val,_val2,sizeof _val);
			_val[mp[i][j]]=0;
		//  cerr << maxflow() << endl;
			tmp=maxflow();
			if (tmp!=ans)
				printf("%d %d\n",i,j);
		}
	return 0;
}
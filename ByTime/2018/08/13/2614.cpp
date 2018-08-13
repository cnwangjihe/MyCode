#include <bits/stdc++.h>

using namespace std;

const int MAXN = 509,
		  MAXM = 1009,
		  INF  = 100000009;

int _head[MAXN],_next[MAXM*2],_node[MAXM*2],_val[MAXM*2];
int dis[MAXN],line[MAXN];
bool _in[MAXN];
int ban[MAXN][1009];
int n,m,fp=0;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

int SPFA()
{
	int head=0,tail=0,u,v,tmp;
	line[tail++]=1;
	dis[1]=0;
	_in[1]=1;
	while (head!=tail)
	{
		u=line[head++];
		head%=MAXN;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			tmp=dis[u]+_val[i];
			tmp+=ban[v][tmp];
			if (tmp<dis[v])
			{
				dis[v]=tmp;
				if (!_in[v])
					line[tail++]=v,tail%=MAXN,_in[v]=1;
			}
		}
		_in[u]=0;
	}
	return dis[n];
}

int main()
{
	freopen("2614.in","r",stdin);
	freopen("2614.out","w",stdout);
	memset(_head,-1,sizeof _head);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		_connect(x,y,z);
		_connect(y,x,z);
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		dis[i]=INF;
		for (int j=0;j<x;j++)
		{
			scanf("%d",&y);
			ban[i][y]=1;
		}
		for (int j=1000;~j;j--)
			ban[i][j]+=ban[i][j+1];
		int d=0;
		for (int j=1000;~j;j--)
		{
			ban[i][j]-=d;
			if (ban[i][j]==ban[i][j+1])
				d+=ban[i][j],ban[i][j]=0;
		//	cerr << ban[i][j] << ' ';
		}
	//	cerr << '\n';
	}
	printf("%d\n",SPFA());
	return 0;
}

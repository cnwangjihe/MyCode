#include <bits/stdc++.h>

using namespace std;


const long long INF=1e18;

const int MAXN = 2009,
		  MAXM = 6009;

long long dis[MAXN];
bool _in[MAXN];
int _head[MAXN],_next[MAXM],_node[MAXM];
long long _val[MAXM];
int n,m,k,fp=0;

priority_queue< pair<int,long long> ,vector< pair<int,long long> >,greater< pair<int,long long> > > que;

long long spfa(int s,int t)
{
	for (int i=1;i<=n;i++)
		dis[i]=INF,_in[i]=0;
	que.push(make_pair(0,s));
	dis[s]=0;
	int u,v;
	while(!que.empty())
	{
		u=que.top().second;
		que.pop();
		if (_in[u])
			continue;
		_in[u]=1;
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (dis[v]<=max(dis[u],_val[i]))
				continue;
			dis[v]=max(dis[u],_val[i]);
			que.push(make_pair(dis[v],v));
		}
	}
	return dis[t];
}

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

inline long long read()
{
	char ch=0;
	int w=0;
	long long x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}


void solve()
{
	int q;
	q=read();
	char ch;
	int x,y; long long z;
	for (int i=0;i<q;i++)
	{
		do {ch=getchar();}
			while (ch!='g' && ch!='a');
		if (ch=='a')
		{
			x=read(),y=read(),z=read();
			_connect(x,y,z);
			_connect(y,x,z);
		}
		else
		{
			long long ans=0;
			for (int j=0;j<k;j++)
			{
				x=read(),y=read();
				ans^=spfa(x,y);
			}
			if (ans)
				puts("TimeCome");
			else
				puts("TimeGone");
		}
	}
}

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	
	memset(_head,-1,sizeof _head);
	
	n=read(),m=read(),k=read();
	int x,y; long long z;

	for (int i=0;i<m;i++)
	{
		x=read(),y=read(),z=read();
		_connect(x,y,z);
		_connect(y,x,z);
	}
	
	solve();
	return 0;
}
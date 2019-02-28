// Date      : 2019-02-18 08:17:13
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P5222
// Algorithm : Ek费用流,SPFA(0,1,-1优化)
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 53,
		  MAXM = 1000009,
		  MAXT = 1003,
		  MAXK = MAXT*2,
		  MAXP = MAXK*MAXN,
		  MAXE = MAXP*6 + MAXN*2,
		  INF  = 100000009;

int _head[MAXP],_node[MAXE],_val[MAXE],_next[MAXE],_cost[MAXE];
int from[MAXP],dis[MAXP],que[MAXP];
bool _in[MAXP];
int cost[MAXN],cvt[MAXM],x[MAXT],y[MAXT];
bool ext[MAXM],mp[MAXN][MAXK];
int n,m,k,q,t,fp=0;
int S,T,cnt=0;

inline void _connect(int a,int b,int v,int w)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_cost[fp]=w;
	_head[a]=fp++;
	return ;
}

inline void Connect(int a,int b,int v,int w) {_connect(a,b,v,w),_connect(b,a,0,-w);}
inline int GetNum(int i,int j) {return i*k+j;}

bool SPFA()
{
	int head=0,tail=0,u,v;
	memset(dis,0x3f,sizeof dis);
	memset(from,-1,sizeof from);
	memset(_in,0,sizeof _in);
	que[tail++]=S;
	dis[S]=0;
	_in[S]=1;
	while (head!=tail)
	{
		u=que[head++],head%=MAXP;
		for (int i=_head[u];~i;i=_next[i])
		{
			if (_val[i]<=0)
				continue;
			v=_node[i];
			if (dis[v]>dis[u]+_cost[i])
			{
				dis[v]=dis[u]+_cost[i],from[v]=i;
				if (!_in[v])
				{
					if (dis[v]<dis[que[head]])
						que[((--head)+MAXP)%MAXP]=v;
					else
						que[tail++]=v,tail%=MAXP;
					_in[v]=1;
				}
			}
		}
		_in[u]=0;
	}
	return (~from[T]);
}

int GetCost()
{
	int flow=INF;
	for (int i=T;i!=S;i=_node[from[i]^1])
		flow=min(flow,_val[from[i]]);
	for (int i=T;i!=S;i=_node[from[i]^1])
		_val[from[i]]-=flow,_val[from[i]^1]+=flow;
	return dis[T]*flow;
}

int Solve(int v)
{
	int l=0,r=cnt+1,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (cost[mid]<=v)
			l=mid;
		else
			r=mid;
	}
	return l;
}

int main()
{
//	freopen("P5222.in","r",stdin);
//	freopen("P5222.out","w",stdout);
	memset(_head,-1,sizeof _head);
	scanf("%d%d%d%d",&n,&m,&t,&q);
	for (int i=0;i<t;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		x[i]--,y[i]--;
		ext[y[i]]=1;
	}
	int last=1;
	for (int i=0;i<m;i++)
	{
		if (ext[i] || last)
		{
			last=ext[i];
			cvt[i]=k++;
		}
	}
	for (int i=0;i<t;i++)
	{
		y[i]=cvt[y[i]];
		mp[x[i]][y[i]]=1;
	}
	S=n*k,T=n*k+1;
	for (int i=0;i<n;i++)
		for (int j=0;j<k;j++)
		{
			if (mp[i][j])
				continue;
			if (i+1<n && !mp[i+1][j])
				Connect(GetNum(i,j),GetNum(i+1,j),INF,1);
			if (i && !mp[i-1][j])
				Connect(GetNum(i,j),GetNum(i-1,j),INF,1);
			if (j+1!=k && !mp[i][j+1])
				Connect(GetNum(i,j),GetNum(i,j+1),1,0);
		}
	for (int i=0;i<n;i++)
	{
		Connect(S,GetNum(i,0),1,0);
		Connect(GetNum(i,k-1),T,1,0);
	}
	cnt=0;
	while (SPFA())
		cost[cnt+1]=cost[cnt]+GetCost(),cnt++;
	int v;
	for (int i=0;i<q;i++)
	{
		scanf("%d",&v);
		printf("%d\n",Solve(v));
	}
	return 0;
}
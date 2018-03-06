#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int cx[] = {-1,-1,-1,0,0,1,1,1},
		  cy[] = {-1,0,1,-1,1,-1,0,1};

const int MAXN = 25,
		  MAXP = MAXN*MAXN*3,
		  INF  = 0x7fffffff;

int _next[MAXN*MAXP],_node[MAXN*MAXP],_val[MAXN*MAXP],_cost[MAXN*MAXP],_head[MAXP];
bool _in[MAXP];
int dis[MAXP],from[MAXP],line[MAXP];
int lim[MAXN][MAXN],beg[MAXN][MAXN],end[MAXN][MAXN];
int n,m,ans=0,fp=0,S,T,cnt=0,flowsum=0,tmp;


void _add(int a,int b,int v,int c)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_cost[fp]=c;
	_head[a]=fp++;
	return ;
}

void _connect(int a,int b,int v,int c)
{
	_add(a,b,v,c);
	_add(b,a,0,-c);
	return ;
}

bool dig(char c) {return c>='0' && c<='9';}
int pos1(int a,int b) {return a*m+b;}
int pos2(int a,int b) {return (a+n)*m+b;}
bool _check(int x,int y) {return !(x<0 || y<0 || x>=n || y>=m);}

bool SPFA()
{
	int head=0,tail=0,u,v;
	memset(dis,0x3f,sizeof dis);
	memset(from,-1,sizeof from);
	memset(_in,0,sizeof _in);
	line[tail++]=S;
	dis[S]=0;
	_in[S]=1;
	while (head!=tail)
	{
		u=line[head++];
	//	cerr << dis[u] << endl;
		head%=MAXP;
		for (int i=_head[u];~i;i=_next[i])
		{
			if (_val[i]<=0)
				continue;
			v=_node[i];
			if (dis[u]+_cost[i]<dis[v])
			{
					dis[v]=dis[u]+_cost[i];from[v]=i;
				if (!_in[v])
					_in[v]=1,line[tail++]=v,tail%=MAXP;
			}
		}
		_in[u]=0;
	}
	return (~from[T]);
}

int _getcost()
{
	int flow=INF;
	for (int i=T;i!=S;i=_node[from[i]^1])
		flow=min(flow,_val[from[i]]);
	for (int i=T;i!=S;i=_node[from[i]^1])
		_val[from[i]]-=flow,_val[from[i]^1]+=flow;
	flowsum+=flow;
	return dis[T]*flow;
		
}

int main()
{
	scanf("%d%d",&n,&m);
	memset(_head,-1,sizeof _head);
	S=n*m*2;T=n*m*2+1;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			do {beg[i][j]=getchar();}
				while (!dig(beg[i][j]));
			beg[i][j]-='0';
			cnt+=beg[i][j];
			if (beg[i][j]) 
				_connect(S,pos1(i,j),1,0);
		}
	tmp=cnt;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			do {end[i][j]=getchar();}
				while (!dig(end[i][j]));
			end[i][j]-='0';
			tmp-=end[i][j];
			if (end[i][j]) 
				_connect(pos1(i,j),T,1,0);
		}
	if (tmp)
		return printf("-1\n")&0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			do {lim[i][j]=getchar();}
				while (!dig(lim[i][j]));
			lim[i][j]-='0';
			if (beg[i][j] && !end[i][j])
				_connect(pos1(i,j),pos2(i,j),(lim[i][j]+1)/2,1);
			else
			if (!beg[i][j] && end[i][j])
				_connect(pos1(i,j),pos2(i,j),(lim[i][j]-1)/2,1);
			else
				_connect(pos1(i,j),pos2(i,j),lim[i][j]/2,1);
		}
	int nx,ny;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			for (int k=0;k<8;k++)
			{
				nx=i+cx[k],ny=j+cy[k];
				if (!_check(nx,ny))
					continue;
				_connect(pos2(i,j),pos1(nx,ny),INF,0);
			}
		}
	while (SPFA())
	{
		ans+=_getcost();
	//	cerr << ans << ' ';
	}
	printf("%d\n",(cnt!=flowsum)?-1:ans);
}

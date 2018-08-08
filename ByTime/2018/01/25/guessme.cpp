#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <map>

using namespace std;

//struct Tnode {int x,y,i;};

map <int,int> X,Y;

//bool _cmpx(Tnode a,Tnode b) {return a.x==b.x?a.y<b.y:a.x<b.x;}

void _add(int a,int b,int v,int cost)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_cst[fp]=cost;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
	
}
bool spfa()
{
	bool flag=0;
	int head=0,tail=0,u;
	memset(dis,0x7f,sizeof dis);
	memset(f,0,sizeof f);
	dis[S]=0;
	line[tail++]=0;
	f[S]=1;
	while (tail!=head)
	{
		u=line[head++];
		if (head==T+1) head=0;
		for (int i=_head[u];~i;i=_next[i]) 
		{
			v=_node[i];
			if(_val[i] && dis[v]>dis[u] + _cst[i])
			{
				dis[v]=dis[u]+_cst[i]; 
				pre[v]=u;
				num[v]=i;
				if(!f[v])
				{
					f[i]=1;  
					line[tail++]=v;
					if (tail==T+1) tail=0;  
				}
			}
		f[u]=0;
		if (u==T) flag=1;
	}
	return flag;  
}  

void calcans()
{
	int sum = inf;
	for(int i=T;~i;i=pre[i])
		sum=min(sum, _val[pre[i]][i]);
	for(int i=T;~i;i=pre[i])
	{
		cap[pre[i]][i] -= sum;
		cap[i][pre[i]] += sum;
		ans += cost[pre[i]][i] * sum;
	}
}  

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",x,y);
		if (X.count(x))
			x = X[x];
		else
			x = X[x] = nx++;
		if (Y.count(y))
			y = Y[y];
		else
			y = Y[y] = ny++;
		cntx[x]++;cnty[y]++;
		p[x][y] = 1;
	}
	S = nx + ny, T = nx + ny + 1;
	for (int x=0;x<nx;x++)
		_add(S,x,cntx[x],0),_add(x,S,0,0);
	for (int y=0;y<ny;y++)
		_add(nx+y,T,cnty[y],0),_add(T,nx+y,0,0);
	for (int x=0;x<nx;x++)
		for (int y=0;y<ny;y++)
			_add(x,nx+y,1,p[x][y]),
			_add(nx+y,x,0,-p[x][y]);
	/*
	sort(node+1,node+1+n,_cmpx);
	int S = nx + ny, T = nx + ny + 1;
	for (int i=1;i<=n;i++)
	{
		_add(0,node[i].x,0,)
		while (node[i].x==node[i+1].x)
		{
			t=0;
			for (int j=1;j<=MAXY;j++)
			{
				if (node[i].y!=j)
				{
					_add(node[i].x,j+MAXY,0,1);
					_add(j+MAXY,node[i].x,0,0);
					continue;
				}
				v=1;
				while (node[i].x==node[i+1].x && node[i].y==node[i+1].y)
					i++,v++;
				_add(node[i].x,node[i].y+MAXX,v,v);
				_add(node[i].x,node[i].y+MAXX,0,0);
				i++;
				t+=v;
			}
		}
	}*/
	while (BFS())
	{
		ans+=SPFA();
	}
	return 0;
}

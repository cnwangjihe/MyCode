#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <set>
#include <string.h>

using namespace std;

const int MAXN = 1000009,
		  MAXM = 1005;

const int dx[]={0,1,-1,0},
		  dy[]={1,0,0,-1};

int n,m,k,fp=0;
int val[MAXN],mp[MAXM][MAXM];
int _head[MAXN],_next[MAXN*2],_node[MAXN*2],v[MAXN*2];
long long w[MAXN*2],f[MAXN];
bool filled[MAXM][MAXM];

bool inside(int x,int y) {return x<=n && x>=1 && y>=1 && y<=m;}
void _connect(int a,int b,int vt,long long wt)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	w[fp]=wt;
	v[fp]=vt;
	_head[a]=fp++;
	return ;
}


void build(int x,int y,int fa)
{
	for (int i=0;i<4;i++)
	{
		int nx=x+dx[i],ny=y+dy[i],tx=nx+dx[i],ty=ny+dy[i];
		if (!inside(tx,ty) || (mp[nx][ny]^mp[tx][ty]) || (mp[nx][ny]==fa))
			continue;
		if (filled[tx][ty])
			_connect(fa,mp[nx][ny],1,val[mp[nx][ny]]);
		else
			_connect(fa,mp[nx][ny],0,val[mp[nx][ny]]),
			build(tx,ty,mp[nx][ny]);
	}
}

int calc(int u,int fa)
{
	int ans=0,tmp,vt;
	for(int i=_head[u];~i;i=_next[i])
	{
		vt=_node[i];
		if (vt==fa)
			continue;
		tmp=calc(vt,u);
		if(!tmp && !v[i])
			continue;
		if (v[i])
			f[u]+=w[i],ans=1;
		else
		if (tmp)
			f[u]+=min(f[vt],w[i]),ans=1;
	}
	return ans;
}

int main()
{
	memset(_head,-1,sizeof _head);
	int sx,sy,x,y;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n*m/2;i++)
		scanf("%d",&val[i]);
	for (int i=1;i<=k;i++)
		scanf("%d%d",&x,&y),
		filled[x][y]=1;	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&mp[i][j]);
			if (!mp[i][j])
			{
				sx=i,sy=j;
				if (filled[sx][sy])
					return printf("GG\n"),0;
			}
		}
	build(sx,sy,0);
	calc(0,0);
	printf("%lld\n",f[0]);
	return 0;
}
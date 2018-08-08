#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <queue> 

using namespace std;

const int dx[] = {1,-1,0,0},
		  dy[] = {0,0,1,-1};

struct Tnode {int x,y,step,cos;};

int kcl[11][11][11],num[11][11];
bool vis[11][11][(1<<11)];
int map[11][11][11][11];
queue <Tnode> line;
int n,m,p,k;

int BFS()
{
	int nows=0,cosx;
	for (int i=1;i<=num[1][1];i++)
		nows|=(1<<(kcl[1][1][i]-1));
	vis[1][1][nows]=1;
	line.push((Tnode){1,1,0,nows});
	while (!line.empty())
	{
		Tnode now=line.front();
		line.pop();
		if(now.x==n && now.y==m)
			return now.step; 
		for(int i=0;i<4;i++) 
		{
			int nx=now.x+dx[i],ny=now.y+dy[i],t;
			if (nx<1 || ny<1 || nx>n || ny>m || (map[now.x][now.y][nx][ny]==-1) || 
				((t=map[now.x][now.y][nx][ny]) && (!(now.cos&(1<<(t-1))))) )
				continue;
			cosx=now.cos;
			for (int j=1;j<=num[nx][ny];j++)
				cosx|=(1<<(kcl[nx][ny][j]-1));
			if (vis[nx][ny][cosx])
				continue;
			vis[nx][ny][cosx]=1;
			line.push((Tnode){nx,ny,now.step+1,cosx});
		 }
	}
	return -1;
}

int main()
{
	int s,x,y,p,x1,x2,y1,y2,g;
	scanf("%d%d%d%d",&n,&m,&p,&k);
	for (int i=0;i<k;i++)
	{
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&g);
		map[x1][y1][x2][y2]=map[x2][y2][x1][y1]=g?g:-1;
	}
	scanf("%d",&s);
	for (int i=0;i<s;i++)
	{
		scanf("%d%d%d",&x,&y,&p);
		kcl[x][y][++num[x][y]]=p;
	}
	printf("%d\n",BFS());
	return 0;
} 

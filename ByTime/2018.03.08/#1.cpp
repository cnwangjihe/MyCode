#include <cstdio>
#include <iostream>
#include <queue> 
#define il inline 
using namespace std;
bool vis[11][11][(1<<11)];
int map[11][11][11][11];
int pas[11][11][11],num[11][11];
struct node{
    int x,y,step,cos;
}; 
queue <node> dl;
int n,m,p,k;
int dx[]={0,1,-1,0,0},dy[]={0,0,0,1,-1};
il int BFS()
{
    int nows=0;
    for(int i=1;i<=num[1][1];i++)
     nows|=(1<<(pas[1][1][i]-1));
    vis[1][1][nows]=1;
    dl.push((node){1,1,0,nows});
    while(!dl.empty())
    {
        node now=dl.front();
        dl.pop();
        if(now.x==n&&now.y==m)
         return now.step; 
        for(int i=1;i<=4;i++) 
         {
           int xx=now.x+dx[i],yy=now.y+dy[i],t;
           if(xx<1||yy<1||xx>n||yy>m) continue;
           if(map[now.x][now.y][xx][yy]==-1) continue;
           if((t=map[now.x][now.y][xx][yy])!=0)
            if((now.cos&(1<<(t-1)))==0) continue;
           int cosx=now.cos;
           for(int j=1;j<=num[xx][yy];j++)
            cosx|=(1<<(pas[xx][yy][j]-1));
           if(vis[xx][yy][cosx]) continue;
           vis[xx][yy][cosx]=1;
           dl.push((node){xx,yy,now.step+1,cosx});
         }
    }
    return -1;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&p,&k);
    for(int i=1;i<=k;i++)
    {
        int x1,x2,y1,y2,g;
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&g);
        if(g==0) map[x1][y1][x2][y2]=map[x2][y2][x1][y1]=-1;
        else map[x1][y1][x2][y2]=map[x2][y2][x1][y1]=g;
    }
    int s;
    scanf("%d",&s);
    for(int i=1;i<=s;i++)
    {
        int x,y,p;
        scanf("%d%d%d",&x,&y,&p);
        pas[x][y][++num[x][y]]=p;
    }
    printf("%d\n",BFS());
    return 0;
} 

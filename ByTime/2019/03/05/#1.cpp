#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define N 100000
#define inf 1000000000
using namespace std;
int dis[N],_next[N],point[N],v[N],remain[N];
int n,m,k,tot=-1,head,tail,maxflow,mincost,mid,cnt;
int last[N],can[N],a[100][100],f[33][33][33][33],vis[33][33];
int mark[33][33],sz,ch[432][3],deep[N],cur[N],num[N];
int x[10]={0,1,0,-1},y[10]={1,0,-1,0};
int q1[N],q2[N];
char s[100];
void add(int x,int y,int z)
{
   tot++; _next[tot]=point[x]; point[x]=tot; v[tot]=y; remain[tot]=z; 
   tot++; _next[tot]=point[y]; point[y]=tot; v[tot]=x; remain[tot]=0; 	
}
int addflow(int s,int t)
{
	int now=t; int ans=inf;
	while (now!=s)
	{
		ans=min(ans,remain[last[now]]);
		now=v[last[now]^1];
	}
    now=t;
    while (now!=s)
     {
     	remain[last[now]]-=ans;
     	remain[last[now]^1]+=ans;
     	now=v[last[now]^1];
     }
    return ans;
}
void bfs(int s,int t)
{
	for (int i=s;i<=t;i++)
	 deep[i]=t;
	deep[t]=0; 
	queue<int> p; p.push(t);
	while (!p.empty())
	 {
	 	int now=p.front(); p.pop();
	 	for (int i=point[now];i!=-1;i=_next[i])
	      if (deep[v[i]]==t&&remain[i^1])
	       deep[v[i]]=deep[now]+1,p.push(v[i]);
	 }
}
bool isap(int s,int t)
{
	bfs(s,t);
	for (int i=s;i<=t;i++)
	 cur[i]=point[i];
	for (int i=s;i<=t;i++)
	 num[deep[i]]++;
	int now=s; int ans=0;
	while (deep[s]<t)
	{
		if (now==t)
		 {
		 	ans+=addflow(s,t);
		 	now=s;
		 }
		bool f=false;
		for (int i=cur[now];i!=-1;i=_next[i])
		 if (deep[v[i]]+1==deep[now]&&remain[i])
		  {
		  	last[v[i]]=i;
		  	f=true;
		  	cur[now]=i;
		  	now=v[i];
		  	break;
		  }
		if(!f)
		{
			int minn=t;
			for (int i=point[now];i!=-1;i=_next[i])
			 if (remain[i])  minn=min(deep[v[i]],minn);
			if (!--num[deep[now]]) break;
			deep[now]=minn+1;
			num[deep[now]]++;
			cur[now]=point[now];
			if (now!=s)
			 now=v[last[now]^1];
		}
	}
	return ans==cnt;
}
void Bfs(int xl,int yl)
{
	memset(vis,0,sizeof(vis));
	int l=0; int r=1;
	q1[r]=xl; q2[r]=yl;
	f[xl][yl][xl][yl]=0;
	vis[xl][yl]=1;
	while (l!=r)
	 {
	 	l++;
	 	int nowx=q1[l]; int nowy=q2[l]; int t=f[nowx][nowy][xl][yl];
	 	for (int i=0;i<4;i++)
	 	 {
	 	 	int xx=nowx+x[i]; int yy=nowy+y[i];
	 	 	if (xx>0&&yy>0&&xx<=n&&yy<=m&&a[xx][yy]==1&&!vis[xx][yy])
	 	 	  {
	 	 	  	f[xx][yy][xl][yl]=t+1;
	 	 	  	vis[xx][yy]=1;
	 	 	  	r++; q1[r]=xx; q2[r]=yy;
	 	 	  }
	 	 }
	 }
}
int build()
{
	tot=-1; 
	memset(point,-1,sizeof(point));
	memset(_next,-1,sizeof(_next));
	int num=cnt+1+sz*mid;
	for (int i=1;i<=n;i++)
	 for (int j=1;j<=m;j++)
	  {
	  	if (a[i][j]==1)
	  	 {
	  	 	add(1,mark[i][j]+1,1);
	  	 	for (int k=1;k<=sz;k++)
	  	 	 {
	  	 	 	int xx=ch[k][0]; int yy=ch[k][1];
	  	 	 	if (f[i][j][xx][yy]&&f[i][j][xx][yy]<=mid)
	  	 	 	 {
	  	 	 	 	int t=cnt+1+(mark[xx][yy]-1)*mid+f[i][j][xx][yy];
	  	 	 	 	add(mark[i][j]+1,t,1);
	  	 	 	 }
	  	 	 }
	  	  }
	  	 if (a[i][j]==2)
	  	  {
	  	  	for (int k=1;k<=mid;k++)
	  	  	 {
	  	  	 	int t=cnt+1+(mark[i][j]-1)*mid+k;
	  	  	 	add(t,num+mark[i][j],mid-k+1);
	  	  	 }
	  	  	add(num+mark[i][j],num+sz+1,mid);
	  	  }
	  }
	 return num+sz+1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	 {
	 	scanf("%s",s+1);
	 	for (int j=1;j<=m;j++)
	 	 if (s[j]=='.')  a[i][j]=1,cnt++,mark[i][j]=cnt;
	 	 else  if (s[j]=='D') a[i][j]=2;
	 	 else  if (s[j]=='X') a[i][j]=0;
	 }
	for (int i=1;i<=n;i++)
	 for (int j=1;j<=m;j++)
	  if (a[i][j]==2)
	  { 
	    Bfs(i,j),mark[i][j]=++sz,ch[sz][0]=i,ch[sz][1]=j;
	  }
	head=1; tail=m*n;
	int ans=0;
	while (head<=tail)
	 {
	 	mid=(head+tail)/2;
	 	int t=build();
	 	if (isap(1,t))
	 	 ans=mid,tail=mid-1;
	 	else
	 	 head=mid+1;
	 }
	if (!ans)
	 printf("impossible\n");
	else
	 printf("%d\n",ans);
}
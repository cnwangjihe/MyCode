#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxn = 209;
const int INF = 0x7fffffff;

struct edge
{
	int v,n,c;
};

struct graph
{
	edge e[maxn*maxn*4];
	int head[maxn*3],d[maxn*3],cur[maxn*3],en;
	int S,T,n;
	
	void firstset(int s,int t,int N)
	{
		S=s;T=t;n=N;
		en=0;memset(head,-1,sizeof(head));
	}
	
	void addedge(int u,int v,int c)
	{
		e[en].v=v;e[en].c=c;e[en].n=head[u];head[u]=en++;
		e[en].v=u;e[en].c=0;e[en].n=head[v];head[v]=en++;
	} 
	
	bool bfs()
	{
		int i,u;
		queue<int> q;
		for(i=0;i<=n;i++) cur[i]=head[i],d[i]=-1;
		q.push(S);d[S]=0;
		while(!q.empty())
		{
			u=q.front();q.pop();
			for(i=head[u];i!=-1;i=e[i].n) if(e[i].c && d[e[i].v]==-1)
			{
				d[e[i].v]=d[u]+1;
				q.push(e[i].v);
			}
		}
		return d[T]!=-1;
	}
	int dfs(int x,int a)
	{
		if(!a || x==T) return a;
		
		int f,ans=0;
		for(int &i=cur[x];i!=-1;i=e[i].n) if(d[e[i].v]==d[x]+1 && (f=dfs(e[i].v,min(a,e[i].c) )))
		{
			e[i].c-=f;e[i^1].c+=f;
			ans+=f;a-=f;
			if(!a) break;
		}
		return ans;
	}
	int dinic()
	{
		int ans=0;
		while(bfs()) ans+=dfs(S,INF);
		return ans;
	}
}G;

int n;

int main()
{
	
	int ttt;
	scanf("%d",&ttt);
	for (;ttt;ttt--)
	{
		scanf("%d",&n);
		G.firstset(2*n,2*n+1,2*n+1);
		for (int i=0;i<n;i++)
		{
			int t;
			G.addedge(2*n,i,1);
			G.addedge(i+n,2*n+1,1);
			for (int j=0;j<n;j++)
			{
				scanf("%d",&t);
				if(t) G.addedge(i,j+n,1);
			}
		}
		if (G.dinic()==n)
			printf("Yes\n");
		else
			printf("No\n");
	}
	
	return 0;
} 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 219,
		  MAXM = 30019,
		  INF  = 1000000007;

int head[MAXN],dis[MAXN],path[MAXN],q[MAXN];
int list[MAXM],next[MAXM],flow[MAXM],from[MAXM],cost[MAXM];
bool in[MAXN];
int n,k,A,S,T,SS,TT,fp,ans;

void insert(int x,int y,int z,int w)
{
	next[++fp]=head[x];
	head[x]=fp;
	from[fp]=x;
	list[fp]=y;
	flow[fp]=z;
	cost[fp]=w;
}

void calc()
{
	int x=INF;
	for (int i=path[TT];i;i=path[from[i]]) x=min(x,flow[i]);
	for (int i=path[TT];i;i=path[from[i]])
		flow[i]-=x,flow[i^1]+=x,ans+=x*cost[i];
}

bool spfa()
{
	 for (int i=0;i<=TT;i++) dis[i]=INF;
	 int t=0,w=0,x;
	 q[w++]=SS; in[SS]=1; dis[SS]=0;
	 while (t!=w)
	 {
		x=q[t];
		t=(t+1)%MAXN;
		for (int i=head[x];i;i=next[i])
			if (flow[i] && dis[list[i]]>dis[x]+cost[i])
			{
				dis[list[i]]=dis[x]+cost[i];
				path[list[i]]=i;
				if (!in[list[i]])
				{
					in[list[i]]=1;
					q[w]=list[i];
					w=(w+1)%MAXN;
				}
			}
		in[x]=0;
	 }
	 return dis[TT]!=INF;
}

int main()
{
	scanf("%d%d",&n,&k);
	S=0; A=n<<1|1; T=A+1; SS=T+1; TT=SS+1; fp=1;
	for (int i=0;i<n;i++)
		for (int j=1;j<=n-i;j++)
		{
			int x;
			scanf("%d",&x);
			if (!i)
				insert(A,i+j,1,x),insert(i+j,A,0,-x);
			else
				insert(i+n,i+j,1,x),insert(i+j,i+n,0,-x);
		}
	for (int i=1;i<=n;i++)
		insert(i+n,T,1,0),insert(T,i+n,0,0);
	insert(S,A,k,0); insert(A,S,0,0);
	for (int i=1;i<=n;i++) 
		insert(i,TT,1,0),insert(TT,i,0,0);
	for (int i=1;i<=n;i++)
		insert(SS,i+n,1,0),insert(i+n,SS,0,0);
	insert(T,S,INF,0); insert(S,T,0,0);
	while (spfa()) calc();
	printf("%d\n",ans);
	return 0;
}

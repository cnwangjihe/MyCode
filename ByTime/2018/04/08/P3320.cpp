#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <set>

using namespace std;

const int MAXN = 250001,
		  MAXM = 500001;

int bit[19];
int n,m,s;
int head[MAXN],nxt[MAXM],tow[MAXM],vau[MAXM],tmp=1;
int who[MAXN][19],dep[MAXN];
long long dis[MAXN][19];

void _connect(int u,int v,int w)
{
	tmp++;
	nxt[tmp]=head[u];
	head[u]=tmp;
	tow[tmp]=v;
	vau[tmp]=w;
}
int tid[MAXN],tim;
void dfs(int u)
{
	tid[u]=++tim;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=tow[i];
		if(who[u][0]!=v)
		{
			who[v][0]=u;
			dis[v][0]=vau[i];
			dep[v]=dep[u]+1;
			dfs(v);
		}
	}
}
long long dist(int a,int b)
{
	long long ans=0;
	if(dep[a]<dep[b])swap(a,b);
	int lenth=dep[a]-dep[b];
	for(int i=0;bit[i]<=lenth;i++)
		if(lenth&bit[i])
			ans+=dis[a][i],a=who[a][i];
	if(a==b)return ans;
	for(int i=18;i>=0;i--)
		if(who[a][i]!=who[b][i])
			ans+=dis[a][i]+dis[b][i],a=who[a][i],b=who[b][i];
	return ans+dis[a][0]+dis[b][0];
}
long long ans;
struct Node
{
	int id;
	bool operator <(Node b)const
	{
		return tid[id]<tid[b.id];
	}    
};
std::set<Node>Q;
std::set<Node>::iterator last(std::set<Node>::iterator Pos)
{
	if(Pos==Q.begin())Pos=Q.end();
	Pos--;
	return Pos;
}
std::set<Node>::iterator next(std::set<Node>::iterator Pos)
{
	Pos++;
	if(Pos==Q.end())Pos=Q.begin();
	return Pos;
}

set<Node>::iterator Posl,Posr;

int main()
{
	bit[0]=1;
	for(int i=1;i<=18;i++)
		bit[i]=bit[i-1]<<1;
	scanf("%d%d",&n,&m);
	s=1;
	int u,v,w;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		_connect(u,v,w),_connect(v,u,w);
	}
	who[s][0]=s,dep[s]=1;
	dfs(s);
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++)
			who[i][j]=who[who[i][j-1]][j-1],dis[i][j]=dis[i][j-1]+dis[who[i][j-1]][j-1];
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&u);
		if(Q.find((Node){u})!=Q.end())
		{
			if(Q.size()!=1)
			{
				Posl=Posr=Q.find((Node){u});
				Posl=last(Posl),Posr=next(Posr);
				ans-=dist(u,(*Posl).id)+dist(u,(*Posr).id);
				ans+=dist((*Posl).id,(*Posr).id);
			}
			Q.erase((Node){u});
		}
		else
		{
			Q.insert((Node){u});
			if(Q.size()!=1)
			{
				Posl=Posr=Q.find((Node){u});
				Posl=last(Posl),Posr=next(Posr);
				ans+=dist(u,(*Posl).id)+dist(u,(*Posr).id);
				ans-=dist((*Posl).id,(*Posr).id);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
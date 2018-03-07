#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int cx[] = {-1,-1,-1,0,0,1,1,1},
          cy[] = {-1,0,1,-1,1,-1,0,1};

const int MAXN = 1009,
          MAXM = 10009,
          MAXP = MAXN,
          MAXE = MAXN*2+MAXM,
          INF  = 0x7fffffff;

int _next[MAXE*2],_node[MAXE*2],_val[MAXE*2],_head[MAXP],_cost[MAXE*2];
bool _in[MAXP];
int from[MAXP],line[MAXP];
long long dis[MAXP];
int n,m,fp=0,S,T;
long long ans=0;


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
            if (_val[i]<=0ll)
                continue;
            v=_node[i];
            if (dis[v]>dis[u]+(long long)_cost[i])
            {
                dis[v]=dis[u]+(long long)_cost[i],from[v]=i;
                if (!_in[v])
                    _in[v]=1,line[tail++]=v,tail%=MAXP;
            }
        }
        _in[u]=0;
    }
    return (~from[T]);
}

long long _getcost()
{
    int flow=INF;
    for (int i=T;i!=S;i=_node[from[i]^1])
        flow=min(flow,_val[from[i]]);
    for (int i=T;i!=S;i=_node[from[i]^1])
        _val[from[i]]-=flow,_val[from[i]^1]+=flow;
//	flowsum+=flow;
    return dis[T]*(long long)flow;
        
}

int main()
{
    int v,l,r,c;
    scanf("%d%d",&n,&m);
    memset(_head,-1,sizeof _head);
    S=0,T=n+2;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&v);
        _connect(i,i+1,INF-v,0);
    }
    _connect(S,1,INF,0);
    _connect(n+1,T,INF,0);
    for (int i=0;i<m;i++)
    {
        scanf("%d%d%d",&l,&r,&c);
        _connect(l,r+1,INF,c);
    }
    while (SPFA())
        ans+=_getcost();
    printf("%lld\n",ans);
}

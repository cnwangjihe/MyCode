#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 20005
#define MAXM 25005
using namespace std;
const int inf=1e8;

int n, m, val[MAXN], ans;
int power[15], f[15][59060], d[MAXN], tmp[MAXN];
bool vis[MAXN];

struct node
{
    int v, next;
}edge[MAXM<<1];
int adj[MAXN], pos;

void add(int a,int b)
{
    edge[pos].v=b, edge[pos].next=adj[a];
    adj[a]=pos;++pos;
}

void dfs(int u)
{
    vis[u]=1;
    int v, dep=d[u];
    if(!dep)f[0][0]=val[u], f[0][1]=0, f[0][2]=inf;
    else
    {
        int cnt=0;
        for(int p=adj[u];~p;p=edge[p].next)
            if(vis[(v=edge[p].v)]&&d[v]<dep)
                tmp[++cnt]=d[v];
        for(int s=0;s<power[dep+1];++s)f[dep][s]=inf;
        for(int s=0, t, l;s<power[dep];++s)
        {
            t=1, l=s;
            for(int i=1;i<=cnt;++i)
                if(s/power[tmp[i]]%3==0)t=2;
                else if(s/power[tmp[i]]%3==1)l+=power[tmp[i]];
            f[dep][s+t*power[dep]]=min(f[dep][s+t*power[dep]],f[dep-1][s]);
            f[dep][l]=min(f[dep][l],f[dep-1][s]+val[u]);
        }
    }

    for(int p=adj[u];~p;p=edge[p].next)
        if(!vis[(v=edge[p].v)])
        {
            d[v]=dep+1;
            dfs(v);
            for(int s=0;s<power[dep+1];++s)
                f[dep][s]=min(f[dep+1][s],f[dep+1][s+2*power[dep+1]]);
        }
}

int main()
{
    power[0]=1;
    for(int i=1;i<15;++i)power[i]=power[i-1]*3;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&val[i]);
        adj[i]=-1;
    }
    int u, v;
    while(m--)
    {
        scanf("%d%d",&u,&v);
        add(u,v), add(v,u);
    }
    for(int i=1;i<=n;++i)
        if(!vis[i])
        {
            dfs(i);
            ans+=min(f[0][0],f[0][2]);
        }
    printf("%d\n",ans);
    return 0;
}
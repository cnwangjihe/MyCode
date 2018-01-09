#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+10;
int n,m,tot,st,cs,cnt,q;
int head[MAXN],fa[MAXN],sta[MAXN],dis[MAXN];
int dfn[MAXN],low[MAXN],col[MAXN],A[MAXN],dep[MAXN];
int f[MAXN][23];
bool vis[MAXN];

struct Tway
{
    int u,v,w,nex;
};
Tway e[MAXN<<1];

void add(int u,int v,int w)
{
    ++tot;
    e[tot].u=u;e[tot].v=v;e[tot].w=w;
    e[tot].nex=head[u];head[u]=tot;
}

int findf(int x)
{
    return fa[x]==x?x:fa[x]=findf(fa[x]);
}

void tarjan(int u,int ff)
{
    vis[u]=true;sta[++st]=u;
    dfn[u]=low[u]=++cnt;
    for(int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(ff==v)
            continue;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else
        if(dfn[v]<dfn[u])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        int v=sta[st--];vis[v]=false;col[v]=++cs;
        for(;st && v!=u;v=sta[st--],vis[v]=false,col[v]=cs);
    }
}

void dfs(int u,int ff)
{
    f[u][0]=ff;
    for(int i=1;i<22;++i)
        f[u][i]=f[f[u][i-1]][i-1];
    for(int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==ff)
            continue;
        dep[v]=dep[u]+1;dis[v]=dis[u]+A[v]+e[i].w;
        dfs(v,u);
    }
}

int lca(int x,int y)
{
    if(dep[x]<dep[y])
        swap(x,y);
    for(int i=dep[x]-dep[y],j=0;i;i>>=1,++j)
        if(i&1)
            x=f[x][j];
    if(x==y)
        return x;
    for(int i=21;i>=0;--i)
        if(f[x][i]!=f[y][i])
            x=f[x][i],y=f[y][i];
    return f[x][0];
}

int main()
{
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            tarjan(i,0);
    
    memset(head,0,sizeof(head));
    for(int i=1;i<=n;++i)
        fa[i]=i;
    for(int i=1;i<=2*m;i+=2)
    {
        int u=col[e[i].u],v=col[e[i].v];
        if(u==v)
            A[u]+=e[i].w;
        else
        {
            int fx=findf(u),fy=findf(v);
            if(fx!=fy)
            {
                add(u,v,e[i].w);add(v,u,e[i].w);
                fa[fx]=fy;
            }
        }
    }
    dfs(1,0);
    
    scanf("%d",&q);
    while(q--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        int gf=lca(col[u],col[v]);
        if(dis[col[u]]+dis[col[v]]-2*dis[gf]+A[gf])
            puts("YES");
        else
            puts("NO");
    }
    
    return 0;
}

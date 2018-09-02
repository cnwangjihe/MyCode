#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#define inf 2000000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,cnt,scc,ind,top;
int v[105],w[105];
int sv[105],sw[105];
int dfn[105],low[105],belong[105];
int q[105],f[105][505],in[505];
struct edge{
    int to,next;
}e[505],ed[505];int last[105],last2[105];
bool inq[105];
void insert(int u,int v)
{
    e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
}
void insert2(int u,int v)
{
    in[v]=1;
    ed[++cnt].to=v;ed[cnt].next=last2[u];last2[u]=cnt;
}
void tarjan(int x)
{
    int now=0;
    low[x]=dfn[x]=++ind;
    q[++top]=x;inq[x]=1;
    for(int i=last[x];i;i=e[i].next)
        if(!dfn[e[i].to])
        {
            tarjan(e[i].to);
            low[x]=min(low[x],low[e[i].to]);
        }
        else if(inq[e[i].to])
            low[x]=min(low[x],dfn[e[i].to]);
    if(low[x]==dfn[x])
    {
        scc++;
        while(now!=x)
        {
            now=q[top--];inq[now]=0;
            belong[now]=scc;
            sv[scc]+=v[now];
            sw[scc]+=w[now];
        }
    }
}
void rebuild()
{
    cnt=0;
    for(int x=1;x<=n;x++)
        for(int i=last[x];i;i=e[i].next)
            if(belong[e[i].to]!=belong[x])
                insert2(belong[x],belong[e[i].to]);
}
void dp(int x)
{
    for(int i=last2[x];i;i=ed[i].next)
    {
        dp(ed[i].to);
        for(int j=m-sw[x];j>=0;j--)
        {
            for(int k=0;k<=j;k++)
                f[x][j]=max(f[x][j],f[x][k]+f[ed[i].to][j-k]);      
        }
    }
    for(int j=m;j>=0;j--)
    {
        if(j>=sw[x])f[x][j]=f[x][j-sw[x]]+sv[x];
        else f[x][j]=0;
    }
}
int main()
{
    freopen("install.in","r",stdin);
    freopen("install.out","w",stdout);
    n=read();m=read();
    for(int i=1;i<=n;i++)w[i]=read();
    for(int i=1;i<=n;i++)v[i]=read();
    for(int i=1;i<=n;i++)
    {
        int x=read();
        if(x)insert(x,i);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])tarjan(i);
    rebuild();
    for(int i=1;i<=scc;i++)
        if(!in[i])
            insert2(scc+1,i);
    dp(scc+1);
    printf("%d\n",f[scc+1][m]);
    return 0;
}
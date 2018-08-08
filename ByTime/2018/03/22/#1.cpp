#include<iostream>
#include<cstdio>
#include<queue>
#define MAXN (65534+5)
using namespace std;
int head1[MAXN],head[MAXN],num1,num2;
int n,ind[MAXN],sum,topo[MAXN];
int father[MAXN],f[MAXN][17],depth[MAXN];
int SUM[MAXN];
struct node1
{
    int to,next;
}edge1[MAXN*4];
void add1(int u,int v)
{
    edge1[++num1].to=v;
    edge1[num1].next=head1[u];
    head1[u]=num1;
}
struct node
{
    int to,next;
}edge[MAXN*2+10];
void add(int u,int v)
{
    edge[++num2].to=v;
    edge[num2].next=head[u];
    head[u]=num2;
}
void toposort()
{
    queue<int>q;
    for (int i=1;i<=n;++i)
        if(ind[i]==0)
            q.push(i);
    while (!q.empty())
    {
        int x=q.front();
        q.pop();
        topo[++sum]=x;
        for (int i=head1[x];i!=0;i=edge1[i].next)
        {
            ind[edge1[i].to]--;
            if(!ind[edge1[i].to]) 
                q.push(edge1[i].to);
        }
    }    
}
void RMQ(int x)
{
    f[x][0]=father[x];
    for (int i=1;i<=16;++i)
        f[x][i]=f[f[x][i-1]][i-1];
}
int LCA(int x,int y)
{
    if (depth[x]<depth[y])    swap(x,y);
    for (int i=16;i>=0;--i)
        if (f[x][i]!=0&&depth[f[x][i]]>=depth[y])
            x=f[x][i];
    if (x==y)    return y;
    for (int i=16;i>=0;--i)
        if (f[x][i]!=0&&f[y][i]!=0&&f[x][i]!=f[y][i])
        {
            x=f[x][i];
            y=f[y][i];
        }
    return father[x];
}
void build()
{
    depth[n+1]=1;
    father[n+1]=n+1;
    for (int i=n;i>=1;--i)
    {
        int x=topo[i];
        if (head1[x]==0)
        {
            father[x]=n+1;
            add(n+1,x); 
            f[x][0]=n+1;
            depth[x]=2;
            continue;
        }
        int lca=edge1[head1[x]].to;
        for (int i=edge1[head1[x]].next;i!=0;i=edge1[i].next)
        {
            lca=LCA(lca,edge1[i].to);
        }
        father[x]=lca;
        add(father[x],x); 
        depth[x]=depth[father[x]]+1;
        RMQ(x);
    }
}
void DPtree(int x)
{
    SUM[x]=1;
    for (int i=head[x];i!=0;i=edge[i].next)
    {
        DPtree(edge[i].to);
        SUM[x]+=SUM[edge[i].to];
    }
}
int main()
{
    int x;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&x);
        while (x!=0)
        {
            add1(i,x);
            ++ind[x];
            scanf("%d",&x);
        }
    }
    toposort();
    build();
    DPtree(n+1); 
    for (int i=1;i<=n;++i)
        printf("%d\n",SUM[i]-1);
}
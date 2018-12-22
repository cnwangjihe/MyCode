#include<cstdio>
#include<algorithm>
#include<cstring>
#include <fstream>
using namespace std;
const int maxn=300010;
struct node{
    int to,next,w;
}edge[maxn*2];
struct no{
    int u,v,lcaa,diss;
}lu[maxn*2];
int summ,cnt=0,k,n,m,num[maxn],mi[maxn],vis[maxn];
int temp[maxn],head[maxn],deep[maxn],dis[maxn];
int fa[maxn][25],dp[maxn][25];
void adde(int u,int v,int w){
    k++;
    edge[k].to=v;
    edge[k].next=head[u];
    edge[k].w=w;
    head[u]=k;
}
void dfs(int x,int pa,int dep){
    cnt++;
    num[cnt]=x;
    deep[x]=dep;
    vis[x]=1;
    for(int i=1;i<25;i++){
        fa[x][i]=fa[fa[x][i-1]][i-1];
    }
    for(int i=head[x];i>0;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v]){
            fa[v][0]=x;
            dis[v]=dis[x]+edge[i].w;
            dfs(v,x,dep+1);
        }
    }
}
int lca(int x,int y){
    if(deep[x]<deep[y]) swap(x,y);
    int t=deep[x]-deep[y];
    for(int i=0;i<25;i++){
        if((1<<i)&t) x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=24;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];y=fa[y][i];
        }
    }
    return fa[x][0];
}
bool check(int mid){
    int cnt=0,ans=0;
    memset(temp,0,sizeof(temp));
    for(int i=1;i<=m;i++){
        if(lu[i].diss>mid){
            temp[lu[i].u]++;temp[lu[i].v]++;temp[lu[i].lcaa]-=2;
            ans=max(ans,lu[i].diss-mid);
            cnt++;
        }
    }
    if(cnt==0) return true;
    for(int i=n;i>=1;i--) temp[fa[num[i]][0]]+=temp[num[i]];
    for(int i=2;i<=n;i++) if(temp[i]==cnt&&dis[i]-dis[fa[i][0]]>=ans) return true;
    return false;
}
int main(){
  freopen("P2680.in","r",stdin);
    ofstream fcheck("std.out");
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++){
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        adde(x,y,w);adde(y,x,w);
        summ+=w;
    }
    dis[1]=0;
    dfs(1,0,1);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&lu[i].u,&lu[i].v);
        lu[i].lcaa=lca(lu[i].u,lu[i].v);
        lu[i].diss=dis[lu[i].u]+dis[lu[i].v]-2*dis[lu[i].lcaa];
        fcheck << "*** : " << lu[i].lcaa << '\n';
    }
    int left=0,right=summ;
    int mid;
    while(left<right){
        mid=(left+right)>>1;
        if(check(mid)) right=mid;
        else left=mid+1;
    }
    printf("%d",left);
    return 0;
}
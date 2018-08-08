#include<bits/stdc++.h>
using namespace std;
const int N=1e3+100,MOD=1e9+7,rev=(MOD+1)>>1;
int val[N],dp[N][N],ans[N],tmp[N];
struct Edge{
    int to,next;
}e[N*2];
int tot,head[N],len;

void add(int &x,int y){
    x+=y;
    if(x>=MOD)
        x-=MOD;
    while(x<0)
        printf("%d %d\n",x,y);
}

void init(){
    memset(head,-1,sizeof(head));
    tot=0;
}

void addedge(int from,int to){
    e[tot]=(Edge){to,head[from]};
    head[from]=tot++;
}

void FWT(int *a,int n){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%MOD,a[i+j+d]=(x-y+MOD)%MOD;
                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+MOD)%MOD;
                //and:a[i+j]=x+y;
                //or:a[i+j+d]=x+y;
            }
}

void UFWT(int *a,int n){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1LL*(x+y)*rev%MOD,a[i+j+d]=(1LL*(x-y)*rev%MOD+MOD)%MOD;
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                //and:a[i+j]=x-y;
                //or:a[i+j+d]=y-x;
            }
}

void solve(int *a,int *b,int n){
    FWT(a,n);
    FWT(b,n);
    for(int i=0;i<n;i++)   a[i]=1LL*a[i]*b[i]%MOD;
    UFWT(a,n);
}

void dfs(int u,int fa){
    for(int i=0;i<len;i++)
        dp[u][i]=0;
    dp[u][val[u]]=1;
    for(int i=head[u];i!=-1;i=e[i].next){
        int v=e[i].to;
        if(v==fa)   continue;
        dfs(v,u);
        for(int i=0;i<len;i++)
            tmp[i]=dp[u][i];
        solve(dp[u],dp[v],len);
        for(int i=0;i<len;i++)
            add(dp[u][i],tmp[i]);
    }
    for(int i=0;i<len;i++)
        add(ans[i],dp[u][i]);
}

int main(){
    int _,n,m,u,v;
    scanf("%d",&_);
    while(_--){
        scanf("%d%d",&n,&m);
        memset(ans,0,sizeof(ans));
        len=1;while(len<m)  len<<=1;
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        dfs(1,0);
        for(int i=0;i<m-1;i++)
            printf("%d ",ans[i]);
        printf("%d\n",ans[m-1]);
    }
    return 0;
}
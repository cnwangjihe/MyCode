#include<cstdio>
#include<cctype>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int read() {
    int x=0,f=1;
    char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}
const int maxn=205;
const int maxm=205;
const int inf=2e9+7;
struct edge {
    int v,w,nxt;
} e[maxm<<1];
int h[maxn],tot,n,m,gap[maxn],last[maxn],d[maxn],que[maxn],ql,qr;
vector<int> inv[maxn];
void add(int u,int v,int w) {
    e[++tot]=(edge){v,w,h[u]};
    h[u]=tot;
    e[++tot]=(edge){u,0,h[v]};
    h[v]=tot;
}
void init(int s,int t) {
    memset(gap,0,sizeof gap),memset(d,0,sizeof d),++gap[d[t]=1];
    for (int i=1;i<=n;++i) last[i]=h[i];
    que[ql=qr=1]=t;
    while (ql<=qr) {
        int x=que[ql++];
        for (int i=h[x],v=e[i].v;i;i=e[i].nxt,v=e[i].v) if (!d[v]) ++gap[d[v]=d[x]+1],que[++qr]=v;
    }
}
int aug(int x,int s,int t,int mi) {
    if (x==t) return mi;
    int flow=0;
    for (int &i=last[x],v=e[i].v;i;i=e[i].nxt,v=e[i].v) if (d[x]==d[v]+1) {
        int tmp=aug(v,s,t,min(mi,e[i].w));
        flow+=tmp,mi-=tmp,e[i].w-=tmp,e[i^1].w+=tmp;
        if (!mi) return flow;
    }
    if (!(--gap[d[x]])) d[s]=n+1;
    ++gap[++d[x]],last[x]=h[x];
    return flow;
}
int maxflow(int s,int t) {
    init(s,t);
    int ret=aug(s,s,t,inf);
    while (d[s]<=n) ret+=aug(s,s,t,inf);
    return ret;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("test.in","r",stdin);
#endif
    while (~scanf("%d%d",&m,&n)) {
        tot=1,memset(h,0,sizeof h);
        for (int i=1;i<=n;++i) inv[i].clear();
        for (int i=1;i<=m;++i) {
            int u=read(),v=read(),w=read();
            add(u,v,w);
            if (w) inv[v].push_back(u);
        }
        int ans=maxflow(1,n);
        printf("%d\n",ans);
    }
    return 0;
}
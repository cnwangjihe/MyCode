#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define maxn 1000005
#define ll long long
using namespace std;
int n,q,OP,head[maxn],f[maxn],w[maxn],tot;
int dfst[maxn],dfsn[maxn],sc,op[maxn],val[maxn];
int t1,t2,t3,li,ri,dy[maxn];
struct node{
    int v,nex;
}e[maxn];
struct no{
    ll v;
}tree[maxn*8];
void lj(int t1,int t2){
    e[++tot].v=t2;e[tot].nex=head[t1];head[t1]=tot;
}
void dfs(int k,int opt){
    dfst[k]=++sc;op[k]=opt;dy[sc]=k;
    for(int i=head[k];i;i=e[i].nex){
        val[e[i].v]=-val[k]+w[e[i].v];
        dfs(e[i].v,-opt);
    }
    dfsn[k]=sc;
}
void build(int k,int L,int R){
    if(L==R){
        tree[k].v=op[dy[L]]*val[dy[L]];return;
    }
    int mid=L+R>>1;
    build(k*2,L,mid);build(k*2+1,mid+1,R);
}
void ch(int k,int v,int l,int r){
     
    if(l>=li&&r<=ri){
        tree[k].v+=v;
        //cout<<"change "<<tree[k].l<<' '<<tree[k].r<<' '<<tree[k].v<<endl;
        return;
    }
    int mid=l+r>>1;
    if(li<=mid)ch(k*2,v,l,mid);
    if(ri>mid)ch(k*2+1,v,mid+1,r);
}
ll ask(int k,int pl,int opt,ll now,int l,int r){
    now+=opt*tree[k].v;
    if(l==r)return now;
    //cout<<tree[k].l<<' '<<tree[k].r<<' '<<now<<endl; 
    int mid=l+r>>1;
    if(pl<=mid)return ask(k*2,pl,opt,now,l,mid);
    else return ask(k*2+1,pl,opt,now,mid+1,r);
}
int get(){
    int v=0;char ch;
    while(!isdigit(ch=getchar()));v=v+ch-48;
    while(isdigit(ch=getchar()))v=(v<<3)+(v<<1)+ch-48;
    return v;
}
int main()
{
    freopen("equation.in","r",stdin);
    freopen("#2.out","w",stdout);
    cin>>n>>q;
    for(int i=2;i<=n;i++){
        scanf("%d%d",&f[i],&w[i]);
        lj(f[i],i);
    }
    dfs(1,1);build(1,1,n);
    //for(int i=1;i<=n;i++)cout<<i<<' '<<val[i]<<' '<<op[i]<<endl;
    for(int i=1;i<=q;i++){
        scanf("%d",&OP);
        if(OP==1){
            scanf("%d%d%d",&t1,&t2,&t3);
            ll v1=ask(1,dfst[t1],op[t1],0,1,n),v2=ask(1,dfst[t2],op[t2],0,1,n);
            if(op[t1]+op[t2]==0){
                if(v1+v2==t3)puts("inf");
                else puts("none");
            }
            else {
                ll tmp=t3-v1-v2;
                if(tmp%2==0)printf("%lld\n",tmp/2*op[t1]);
                else puts("none");
            }
        }
        else {
            scanf("%d%d",&t1,&t2);
            li=dfst[t1],ri=dfsn[t1];
            ch(1,-op[t1]*w[t1],1,n);w[t1]=t2;
            ch(1,op[t1]*w[t1],1,n);
        }
    }
    return 0;
}
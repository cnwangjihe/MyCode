#include<bits/stdc++.h>
using namespace std;
 
const int N=2e5+10;
int n,m;
int A[N],B[N];
 
struct Tree
{
    int mx,mi;
};
Tree tr[N<<2];
 
void pushup(int rt,int pos)
{
    if(tr[rt<<1].mi==-1)
        tr[rt].mi=-1;
    else
    if(A[pos]>=tr[rt<<1].mi)
        tr[rt].mi=tr[rt<<1|1].mi;
    else
    if(B[pos]>=tr[rt<<1].mi)
        tr[rt].mi=tr[rt<<1|1].mx;
    else
        tr[rt].mi=-1;
 
    if(tr[rt<<1].mx==-1)
        tr[rt].mx=-1;
    else
    if(A[pos]>=tr[rt<<1].mx)
        tr[rt].mx=tr[rt<<1|1].mi;
    else
    if(B[pos]>=tr[rt<<1].mx)
        tr[rt].mx=tr[rt<<1|1].mx;
    else
        tr[rt].mx=-1;
}
 
void build(int rt,int l,int r)
{
    if(l==r)
    {
        tr[rt].mi=A[l];
        tr[rt].mx=B[l];
        return;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt,mid+1);
}
 
void update(int rt,int l,int r,int p)
{
    if(l==r)
    {
        tr[rt].mi=A[l];
        tr[rt].mx=B[l];
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid)
        update(rt<<1,l,mid,p);
    else
        update(rt<<1|1,mid+1,r,p);
    pushup(rt,mid+1);
}
 
int main()
{
    freopen("gwent.in","r",stdin);
    freopen("#1.out","w",stdout);
     
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&A[i],&B[i]);
        if(A[i]>B[i])
            swap(A[i],B[i]);
    }
    build(1,1,n);
     
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        swap(A[x],A[y]);swap(B[x],B[y]);
        update(1,1,n,x);update(1,1,n,y);
        puts((~tr[1].mi)?"YES":"NO");
    }
     
    return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN=505;
int n;

struct Tnode
{
    int id,num;
};
Tnode a[MAXN],b[MAXN];

void solve(int l,int r,int rt)
{
    if(l>=r || rt>(1<<29))
        return;

    int pl=l,pr=r;
    for(int i=l;i<=r;++i)
        if(a[i].num&rt)
            b[pl++]=a[i];
        else
            b[pr--]=a[i];
    for(int i=l;i<=r;++i)
        a[i]=b[i]; 

    solve(l,pl-1,rt<<1);
    solve(pr+1,r,rt<<1);
}

int main()
{
 //   freopen("UOJ143.in","r",stdin);
   // freopen("UOJ143.out","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].num);
        a[i].id=i;
    }
    solve(1,n,1);
    for(int i=1;i<=n;++i)
        printf("%d ",a[i].id);

    return 0;
}

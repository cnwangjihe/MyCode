#include <bits/stdc++.h>

using namespace std;

struct Data
{
       int x,from,to,id,flag;
       Data(){}
       Data(int _x,int _f,int _t,int _i,int _fl):x(_x),from(_f),to(_t),id(_i),flag(_fl){}
}      a[2000050];

int n,q,tot,tree[2000050],fx[2000050],fy[2000050],tx[2000050],ty[2000050],sx[2000050],sy[2000050];
int ca[2000050],cb[2000050],cc[2000050],cd[2000050];
long long ans[2000050];

bool cmp(Data a,Data b)
{
     return a.x<b.x||a.x==b.x&&a.flag<b.flag;
}

int Ask(int x)
{
int t=0;
    for (;x;x-=x&-x) t+=tree[x];
    return t;
}

void Update(int x)
{
     for (;x<=n;x+=x&-x) tree[x]++;
}

long long C2(long long x)
{
     return x*(x-1)/2;
}

int  main()
{
int  i,x;
     
     
     scanf("%d%d",&n,&q);
     tot=0;
     for (i=1;i<=n;i++)
     {
         scanf("%d",&x);
         a[++tot]=Data(i,x,x,i,1);
         sx[i]++;
         sy[x]++;
     }
     for (i=1;i<=n;i++)
     {
         sx[i]+=sx[i-1];
         sy[i]+=sy[i-1];
     }
     for (i=1;i<=q;i++)
     {
         scanf("%d%d%d%d",&fx[i],&fy[i],&tx[i],&ty[i]);
         a[++tot]=Data(fx[i],fy[i],ty[i],i,0);
         a[++tot]=Data(tx[i],fy[i],ty[i],i,2);
     }
     sort(a+1,a+tot+1,cmp);
     for (i=1;i<=tot;i++)
     if  (a[i].flag==0)
     {
         ca[a[i].id]=Ask(a[i].from-1);
         cb[a[i].id]=Ask(n)-Ask(a[i].to);
     }   else
     if  (a[i].flag==1)
     {
         Update(a[i].from);
     }   else
     {
         cc[a[i].id]-=Ask(a[i].from-1);
         cd[a[i].id]-=Ask(n)-Ask(a[i].to);
     }
     for (i=1;i<=q;i++)
     {
         cc[i]+=Ask(fy[i]-1);
         cd[i]+=Ask(n)-Ask(ty[i]);
         ans[i]=C2(n)-C2(sx[fx[i]-1])-C2(n-sx[tx[i]])-C2(sy[fy[i]-1])-C2(n-sy[ty[i]])+C2(ca[i])+C2(cb[i])+C2(cc[i])+C2(cd[i]);
         printf("%lld\n",ans[i]);
     }
     
     return 0;
}

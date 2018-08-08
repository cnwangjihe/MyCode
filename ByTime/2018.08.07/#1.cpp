#include<bits/stdc++.h>
using namespace std;
#define N 1050

struct Big
{
       int n,d[333];
       Big(){}
       Big(int x)
       {
           n=1;
           memset(d,0,sizeof(d));
           d[1]=x;
       }
};

int tot,arr[N];
bool prime[N];
bitset<N> e[N];
vector<int> vec[N];

void Mul(Big &a,int b)
{
int  i;
     for (i=1;i<=a.n;i++) a.d[i]*=b;
     for (i=1;i<=a.n;i++)
     {
         a.d[i+1]+=a.d[i]/10;
         a.d[i]%=10;
     }
     if  (a.d[a.n+1]>0) a.n++;
}

void Sub(Big &a,int b)
{
int  i;
     a.d[1]-=b;
     for (i=1;i<=a.n;i++)
     if  (a.d[i]<0)
     {
         a.d[i+1]--;
         a.d[i]+=10;
     }
     if  (a.n>1&&a.d[a.n]<=0) a.n--;
}

int  Gaussbit(int n,int m)  //-1 : no sol     0 : single sol    x>0 : x var
{
int  i,j,k,ans;
     for (i=1,j=1;i<=n&&j<=m;i++,j++)
     {
         if  (!e[i].test(j))
         {
             for (k=i+1;k<=n;k++)
             if  (e[k].test(j))
             {
                 swap(e[i],e[k]);
                 break;
             }
         }
         if  (!e[i].test(j))
         {
             i--;
             continue;
         }
         for (k=i+1;k<=n;k++)
         if  (e[k].test(j)) e[k]^=e[i];
     }
     for (i=1;i<=n;i++)
     if  (e[i].count()==1&&e[i].test(m+1)) return -1;
     ans=m;
     for (i=1;i<=n;i++)
     if  (e[i].count()-e[i].test(m+1)>0) ans--;
     return ans;
}

int  main()
{
int  i,j,x,ans,cas,n,size;
Big  cur;
     

 //   freopen("2592.in", "r", stdin);
   // freopen("2592.out", "w", stdout);
     
     memset(prime,true,sizeof(prime));
     prime[1]=false;
     for (i=2;i<N;i++)
     if  (prime[i])
         for (j=i+i;j<N;j+=i) prime[j]=false;
     tot=0;
     for (i=1;i<N;i++)
     if  (prime[i])
     {
         arr[++tot]=i;
     }
     
     for (i=1;i<N;i++)
     {
         x=i;
         for (j=1;j<=tot;j++)
             for (;x%arr[j]==0;x/=arr[j]) vec[i].push_back(j);
     }
     
     scanf("%d",&cas);
     while (cas--)
     {
           scanf("%d",&n);
           for (i=1;i<=tot;i++) e[i].reset();
           for (i=1;i<=n;i++)
           {
               scanf("%d",&x);
               size=vec[x].size();
               for (j=0;j<size;j++) e[vec[x][j]].flip(i);
           }
           ans=Gaussbit(tot,n);
           if  (ans==-1) printf("0\n"); else
           {
               cur=Big(1);
               for (i=1;i<=ans;i++) Mul(cur,2);
               Sub(cur,1);
               for (i=max(cur.n,1);i>=1;i--) printf("%d",cur.d[i]);
               printf("\n");
           }
     }
     
     return 0;
}
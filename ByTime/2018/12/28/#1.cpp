
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
 
#define MEM(a,x) memset(a,x,sizeof a)
#define eps 1e-8
#define MOD 10009
#define MAXN 110
#define MAXM 100010
#define INF 99999999
#define ll __int64
#define bug cout<<"here"<<endl
 
using namespace std;
 
int Read()
{
    char ch;
    int a = 0;
    while((ch = getchar()) == ' ' | ch == '\n');
    a += ch - '0';
    while((ch = getchar()) != ' ' && ch != '\n')
    {
        a *= 10;
        a += ch - '0';
    }
    return a;
}
 
void Print(int a)
{
     if(a>9)
         Print(a/10);
     putchar(a%10+'0');
}
 
int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    if(x<0) return -1;
    else return 1;
}
double b[MAXN][MAXN];
double det(double a[][MAXN],int n)
{
    int i,j,k,sign=0;
    double ret=1;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            b[i][j]=a[i][j];
    for(i=0;i<n;i++)
    {
        if(sgn(b[i][i])==0)
        {
            for(j=i+1;j<n;j++)
                if(sgn(b[j][i])!=0)
                    break;
            if(j==n) return 0;
            for(k=i;k<n;k++)
                swap(b[i][k],b[j][k]);
            sign++;
        }
        ret*=b[i][i];
        for(k=i+1;k<n;k++)
            b[i][k]/=b[i][i];
        for(j=i+1;j<n;j++)
            for(k=i+1;k<n;k++)
                b[j][k]-=b[j][i]*b[i][k];
    }
    if(sign&1) ret=-ret;
    return ret;
}
double a[MAXN][MAXN];
int g[MAXN][MAXN];
 
int main()
{
//    fread;
    int tc;
    scanf("%d",&tc);
    while(tc--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        MEM(g,0);
        while(m--)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            u--; v--;
            g[u][v]=g[v][u]=1;
        }
        MEM(a,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j&&g[i][j])
        {
            a[i][i]++;
            a[i][j]=-1;
        }
        double ans=det(a,n-1);
        printf("%.0lf\n",ans);
    }
    return 0;
}
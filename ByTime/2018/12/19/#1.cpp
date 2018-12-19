#include <bits/stdc++.h>
using namespace std;
#define N 510
#define eps 1e-8
int to[N*N*2],_next[N*N*2],head[N],tot;
int F[N*N],T[N*N];
double q[N*N];
int num[N];
double f[N][N];
double im[N*N*2];
int n,m;
int read() {
    int ans=0,flag=1;
    char ch=getchar();
    while((ch>'9' || ch<'0') && ch!='-') ch=getchar();
    if(ch=='-') flag=-1,ch=getchar();
    while(ch>='0' && ch<='9') ans=ans*10+ch-'0',ch=getchar();
    return ans*flag;
}
void addedge(int u,int v) {
    num[u]++;
    to[++tot]=v;
    _next[tot]=head[u];
    head[u]=tot;
}
int main() {
    n=read(),m=read();
    for(int i=1;i<=m;i++) {
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
        F[i]=u;T[i]=v;
    }
    f[1][n]=1;
    for(int i=1;i<n;i++) {
        f[i][i]=1;
        for(int j=head[i];j;j=_next[j])
            if(to[j]!=n)
                f[i][to[j]]=-1.0/num[to[j]];
    }
    for (int i=1;i<n;i++)
    {
        for (int j=1;j<=n;j++)
            cerr << f[i][j] << ' ';
        cerr << '\n';
    }
    for(int i=1;i<n;i++) {
        int now=i;
        double s=f[i][i];
        for(int j=i+1;j<n;j++)
            if(fabs(s-1.0)-fabs(f[j][i]-1.0)>=eps)
                {now=j;s=f[j][i];}
        if(now!=i) {
            for(int j=1;j<=n;j++)
                swap(f[i][j],f[now][j]);
        }
        for(int j=n;j>=i;j--) f[i][j]/=f[i][i];
        for(int j=1;j<n;j++)
            if(i!=j)
                for(int k=n;k>=i;k--)
                    f[j][k]-=f[j][i]*f[i][k];
    }
    for (int i=1;i<n;i++)
        cerr << f[i][n] << '\n';
    for(int i=1;i<=m;i++) {
        if(F[i]!=n)
            q[i]+=f[F[i]][n]*(1.0/num[F[i]]);
        if(T[i]!=n)
            q[i]+=f[T[i]][n]*(1.0/num[T[i]]);
    }
    sort(q+1,q+m+1);
    double ans=0;
    for(int i=1;i<=m;i++)
        ans+=q[i]*((m-i+1)*1.0);
    printf("%.3lf\n",ans);
    return 0;
}
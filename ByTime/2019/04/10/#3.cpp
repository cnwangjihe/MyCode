#include<iostream>
#include<cstdio>
using namespace std;
const int N=400100;
const int mod=998244353;
int n,m,A[N],B[N],C[N],D[N],F[N],G[N],r[N],l,tt;
int ksm(int a,int k)
{
    int s=1;for(;k;k>>=1,a=1ll*a*a%mod)
    if(k&1) s=1ll*s*a%mod; return s;
}
void Getl(int len)
{
    for(l=1,tt=0;l<=len;l<<=1) tt++;tt--;
    for(int i=0;i<l;i++) r[i]=(r[i>>1]>>1)|((i&1)<<tt);
}
void NTT(int *P,int op)
{
    for(int i=0;i<l;i++) if(i<r[i]) swap(P[i],P[r[i]]);
    for(int i=1;i<l;i<<=1)
    {
        int W=ksm(3,(mod-1)/(i<<1));
        if(op<0) W=ksm(W,mod-2);
        for(int j=0,p=i<<1;j<l;j+=p)
            for(int k=0,w=1;k<i;k++,w=1ll*w*W%mod)
            {
                int X=P[j+k],Y=1ll*P[j+k+i]*w%mod;
                P[j+k]=(X+Y)%mod;P[j+k+i]=((X-Y)%mod+mod)%mod;
            }
    }
    if(op<0) for(int i=0,u=ksm(l,mod-2);i<l;i++) P[i]=1ll*P[i]*u%mod;
}
void GetInv(int *f,int *g,int n)
{
    if(n==1) {g[0]=ksm(f[0],mod-2);return;}
    GetInv(f,g,n>>1); Getl(n);
    for(int i=0;i<n;i++) C[i]=f[i],D[i]=g[i];
    for(int i=n;i<l;i++) C[i]=D[i]=0; NTT(C,1);NTT(D,1);
    for(int i=0;i<l;i++) C[i]=1ll*C[i]*D[i]%mod*D[i]%mod; NTT(C,-1);
    for(int i=0;i<n;i++) g[i]=((2ll*g[i]%mod-C[i])%mod+mod)%mod;
}
void Dao(int *A,int *B,int len)
{
    for(int i=1;i<len;i++) B[i-1]=1ll*i*A[i]%mod;B[len-1]=0;
}
void Jifen(int *A,int *B,int len)
{
    for(int i=1;i<len;i++) B[i]=1ll*A[i-1]*ksm(i,mod-2)%mod;B[0]=0;
}
void Getln(int *f,int *g,int n)
{
    Dao(f,A,n); GetInv(f,B,n);
    Getl(n); NTT(A,1);NTT(B,1);
    for(int i=0;i<l;i++) A[i]=1ll*A[i]*B[i]%mod;
    NTT(A,-1); Jifen(A,g,n);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&F[i]);
    for(m=1;m<=n+1;m<<=1); Getln(F,G,m);
    for(int i=0;i<n+1;i++) printf("%d ",G[i]);
}
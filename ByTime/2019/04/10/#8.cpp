#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<string>
#include<queue>
#include<unordered_map>
#include<set>
#include<stack>
#include<cmath>
#include<cctype>
using namespace std;
const int inf=0x7fffffff;
const double eps=1e-10;
const double pi=acos(-1.0);
//char buf[1<<15],*S=buf,*T=buf;
//char getch(){return S==T&&(T=(S=buf)+fread(buf,1,1<<15,stdin),S==T)?0:*S++;}
inline int read(){
  int x=0,f=1;char ch;ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-') f=0;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
  if(f)return x;else return -x;
}
const int N=13e5+10;
const int mod=998244353,mod_g=3;
int K;
int R[N];
int power(int a,int b){
  int ans=1;
  for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
  return ans;
}
#define Inv(x) power(x,mod-2)
int Polynomial_init(int n){
  int len;for(len=1;len<n;len<<=1);
  return len;
}
int g[22],inv[N];
void Get_Inv(int n){
  inv[1]=1;
  for(int i=2;i<=n;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
inline int add(int a,int b){return (a+=b)>=mod?a-mod:a;}
void NTT(int a[],int f,int Len){
  for(int i=1;i<Len;i++)if(i<R[i])swap(a[i],a[R[i]]);
  static int i,j,k,kk,w,t,wn,r;
  for(k=2,kk=1,r=1;k<=Len;k<<=1,kk<<=1,++r){
    wn=g[r];
    for(i=0;i<Len;i+=k)
    for(j=0,w=1;j<kk;++j,w=1ll*w*wn%mod){
      t=1ll*w*a[i+j+kk]%mod;
      a[i+j+kk]=add(a[i+j],mod-t);
      a[i+j]=add(a[i+j],t);
    }
  }
  if(f==-1){
    reverse(a+1,a+Len);
    for(int i=0;i<Len;++i)a[i]=1ll*a[i]*inv[Len]%mod;
  }
}
void Convolution(int *a,int *b,int la,int lb){
  int n=la,m=lb;
  int L=0;for(m+=n,n=1;n<=m;n<<=1)L++;
  for(register int i=0;i<n;++i)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
  NTT(a,1,n);NTT(b,1,n);
  for(register int i=0;i<=n;++i)a[i]=1ll*a[i]*b[i]%mod;
  NTT(a,-1,n);
}
int I[N],J[N];
void Multiplication(int *a,int *b,int *c,int la,int lb){
  int n=la,m=lb;
  int L=0;for(m+=n,n=1;n<=m;n<<=1)L++;
  for(register int i=0;i<n;++i)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
  for(register int i=0;i<=la;++i) I[i]=a[i];
  for(register int i=0;i<=lb;++i) J[i]=b[i];
  NTT(I,1,n);NTT(J,1,n);
  for(register int i=0;i<=n;++i)c[i]=1ll*I[i]*J[i]%mod,I[i]=J[i]=0;
  NTT(c,-1,n);
}
int C[N];
void Inverse(int *a,int *b,int len){
  if(len==1){b[0]=Inv(a[0]);return;}
  Inverse(a,b,(len+1)>>1);
  int L=0,n=1;
  for(;n<(len<<1);n<<=1)L++;
  for(register int i=1;i<n;++i)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
  for(register int i=0;i<len;++i)C[i]=a[i];
  for(register int i=len;i<n;++i)C[i]=0;
  NTT(C,1,n);NTT(b,1,n);
  for(register int i=0;i<=n;++i)b[i]=1ll*add(2ll,mod-1ll*C[i]*b[i]%mod)*b[i]%mod;
  NTT(b,-1,n);
  for(register int i=len;i<n;++i)b[i]=0;
}
int H[N];
void Derivation(int *a,int *b,int n){
  for(register int i=1;i<n;++i)
  b[i-1]=1ll*i*a[i]%mod;
  b[n-1]=0;
}
void Integral(int *a,int *b,int n){
  for(register int i=1;i<n;++i)
  b[i]=1ll*inv[i]*a[i-1]%mod;
  b[0]=0;
}
int ln_a[N],ln_b[N];
void Logarithmic(int *a,int *b,int n){
  memset(ln_a,0,sizeof(ln_a));
  memset(ln_b,0,sizeof(ln_b));
  Derivation(a,ln_a,n);
  memset(C,0,sizeof(C));
  Inverse(a,ln_b,n);
  Convolution(ln_a,ln_b,n,n);
  Integral(ln_a,b,n);
}
int D[N];
void Exponential(int *a,int *b,int len){
  if(len==1){return;}
  Exponential(a,b,len>>1),Logarithmic(b,D,len);
  D[0]=add(a[0],mod+1ll-D[0]);
  for(register int i=1;i<len;++i) D[i]=add(a[i],mod-D[i]);
  Convolution(b,D,len,len);
  for(register int i=len;i<(len<<1);++i) b[i]=D[i]=0;
}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int BSGS(int a,int b){
  unordered_map<int,int>hash;hash.clear();b%=mod;
  int t=(int)sqrt(mod)+1;
  for(register int j=0;j<t;j++){
    int val=(int)(1ll*b*power(a,j)%mod);
    hash[val]=j;
  }
  a=power(a,t);
  if(a==0){
    if(b==0)return 1;
    else return -1;
  }
  for(register int i=0;i<=t;++i){
    int val=power(a,i);
    int j=hash.find(val)==hash.end()?-1:hash[val];
    if(j>=0&&i*t-j>=0)return i*t-j;
  }
  return -1;
}
int solve(int a,int K){
  int p=BSGS(mod_g,a);
  int ret=power(mod_g,p/K);
  return min(ret,mod-ret);
}
int s_a[N];
void Kth_root(int *a,int *b,int len,int K){
  Logarithmic(a,s_a,len);
  int Kr=Inv(K);
  for(register int i=1;i<=len;++i)s_a[i]=1ll*s_a[i]*Kr%mod;
  b[0]=solve(a[0],K);
  Exponential(s_a,b,len);
}
int n,F[N],G[N],low;
int main()
{
  Get_Inv(N-10);
  for(register int i=1,j=2;i<=19;++i,j<<=1)g[i]=power(mod_g,(mod-1)/j);
  n=read();K=2;
  for(register int i=0;i<n;++i)F[i]=read();
  Kth_root(F,G,Polynomial_init(n),K);
  for(register int i=0;i<n;++i)cout<<G[i]<<" ";
  return 0;
}
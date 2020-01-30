#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mx=1e6+10;
const int mod=998244353;
const double eps=1e-8;
int n,m;
int f[mx];

ll qpow(ll a,int k)
{
	if(!k) return 1;
	if(k==1) return a;
	ll ret=qpow(a,k/2);
	(ret*=ret)%=mod;
	if(k&1) (ret*=a)%=mod;
	return ret;
}
inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}
void init()
{
	n=read();
	for(int i=1;i<=n;i++) f[i]=read();
	for(int i=1;i<=n;i++) m=max(m,f[i]);
}
int a[mx],b[mx];
ll mat[205][205];
int gcd(int a,int b)
{
	if(a%b==0) return b;
	return gcd(b,a%b);
}
void task1()
{
	a[1]=b[1]=1;
	for(int i=2;i<=m;i++) a[i]=(i&1?((i>>1)&1?-1:1)*a[(i>>1)+1]:-a[i>>1]),b[i]=b[i-1]+a[i];
//	for(int i=1;i<=m;i++) a[i<<1]=-a[i],a[(i<<1)-1]=((i-1)&1?-1:1)*a[i];
//	for(int i=2;i<=m;i++) b[i]=b[i-1]+a[i];	
//	for(int i=1;i<=m;i++) cerr<<a[i]<<" "; cerr<<endl;
//	for(int i=1;i<=m;i++) cerr<<b[i]<<" "; cerr<<endl;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mat[i][j]=b[f[gcd(i,j)]];
/*	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) cerr<<mat[i][j]<<" ";
		cerr<<endl;
	}
*/	for(int i=1;i<=n;i++)
	{
		int p=i;
		for(int j=i+1;j<=n;j++) if(abs(mat[j][i])>abs(mat[p][i])) p=j;
		for(int j=1;j<=n;j++) swap(mat[i][j],mat[p][j]);
//		cerr<<i<<endl;
		if(!mat[i][i]) continue;
		for(int j=1;j<=n;j++)
		{
			if(j==i) continue;
			ll t=(mat[j][i]*qpow(mat[i][i],mod-2))%mod;
//			cerr<<i<<" "<<j<<": "<<t<<endl;
			for(int k=1;k<=n;k++) (mat[j][k]-=mat[i][k]*t%mod)%=mod,(mat[j][k]+=mod)%=mod;
		}
/*		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++) cerr<<mat[i][j]<<"\t";
			cerr<<endl;
		}
		cerr<<endl;
*/	}
/*	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) cerr<<mat[i][j]<<"\t";
		cerr<<endl;
	}
*/
	ll det=1;
	for(int i=1;i<=n;i++) mat[i][i]=(mat[i][i]%mod+mod)%mod,(det*=mat[i][i])%=mod;
//	det=min(det,mod-det);
	printf("%lld\n",det);
}

int main()
{
	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	
	init();
	if(n<=200 && m<=1000000) return task1(),0;
	task1();	
	
	return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long ll;
const int mx=3e3+10;
int n;
struct Tnode
{
	int w,r;
};
Tnode a[mx];
ll f[mx][mx],g[mx][mx];

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

bool cmp(Tnode x,Tnode y)
{
	return x.r>y.r;
}

int main()
{
	freopen("angoy.in","r",stdin);
	freopen("angoy.out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)
		a[i].w=read(),a[i].r=read();
	
	sort(a+1,a+n+1,cmp);
	
	ll ans=0;
	
	for(int i=1;i<=n;i++) f[i][0]=a[i].w,g[i][0]=max(g[i-1][0],f[i][0]),ans=max(ans,f[i][0]);
	for(int k=1;k<n;k++)
	{
		g[0][k]=0;
		for(int i=1;i<=n;i++)
		{
			f[i][k]=max(g[i-1][k],g[i-1][k-1]+a[i].w-1ll*k*a[i].r);
			g[i][k]=max(f[i][k],g[i-1][k]);
			ans=max(ans,f[i][k]);
		}
	}
	
/*	for(int k=0;k<n;k++)
	{
		for(int i=1;i<=n;i++)
			cerr<<f[i][k]<<" ";
		cerr<<endl;
	}
*/	
	printf("%lld\n",ans);
	
	return 0;
}

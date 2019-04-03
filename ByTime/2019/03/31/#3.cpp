#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=55;
const ll inf=0x3f3f3f3f3f3f3f3f;
ll n,K,ans;
ll a[N],sum[N],L[N],f[N],g[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return f?ret:-ret;
}
ll C(int l,int r){if(l>r)swap(l,r);return sum[r]-sum[l-1];}
void gmax(ll &x,ll y){x=max(x,y);}
void up(int i,ll x,ll y)
{
	if(f[i]>x) f[i]=x,g[i]=y;
	else if(f[i]==x && g[i]<y) g[i]=y;
}

int main()
{
//	freopen("2843.in","r",stdin);
//	freopen("2843.out","w",stdout);

	int T=read();
	while(T--)
	{
		n=read();K=read();
		for(int i=1;i<=n;++i)
		{
			a[i]=read();sum[i]=sum[i-1]+a[i];L[i]=a[i];
			for(int j=i-1;j;--j) gmax(L[i],C(j,i));
		}
		memset(f,0x3f,sizeof(f));memset(g,0,sizeof(g));
		f[1]=1;g[1]=a[1];
		for(int i=2;i<=n;++i)
		{
			for(int j=1;j<i;++j)
			{
				if(f[j]>=inf) continue;
				if(g[j]+C(j+1,i)>=0) up(i,f[j],g[j]+C(j+1,i));
				else
				{
					if(L[j]<=0) continue;
					ll tmp=(-g[j]-C(j+1,i)-1)/(L[j]*2)+1;
					up(i,f[j]+tmp*2,g[j]+C(j+1,i)+L[j]*2*tmp);
					cerr << tmp << '\n';
				}
			}
			// printf("%lld %lld\n",f[i],g[i]);
		}
		ans=0;
		for(int i=1;i<=n;++i) if(f[i]<=K) gmax(ans,g[i]+L[i]*(K-f[i]));
		printf("%lld\n",ans);
	}
	return 0;
}
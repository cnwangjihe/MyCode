#include<bits/stdc++.h>
#define gc getchar()
#define isd(x) isdigit(x)
#define pb(x) push_back(x)
#define fo(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define add(x,y) {e[++cnt]=(Tedge){y,head[x]};head[x]=cnt;}
#define adds(x,y) {add(x,y);add(y,x);}
#define fi first
#define se second

using namespace std ;

typedef long long ll;
typedef pair<ll,int> pli;

const int N=2e2+10,M=2e6+10,mod=998244353;

namespace IO
{
	int rd(){int x=0,f=1;char c=gc;for(;!isd(c);c=gc)f&=(c!='-');for(;isd(c);c=gc)x=x*10+(c^48);return f?x:-x;}
	void write(int x){if(x>9)write(x/10);putchar(x%10^48);}
	void writes(int x){if(x<0)putchar('-'),x=-x;write(x);putchar(' ');}
	void writeln(int x){if(x<0)putchar('-'),x=-x;write(x);putchar('\n');}
}

using namespace IO;

namespace MS42zz
{
	int A[M],B[M],C[N][N],n,m,ans,f[N];
	int qpow(int x,int y)
	{
		int z=1;
		for (;y;y>>=1,x=1ll*x*x%mod)
			if (y&1) z=1ll*z*x%mod;
		return z;
	}
	int getinv(int x)
	{
		return qpow(x,mod-2);
	}
	void init()
	{
		n=rd();
		for (int i=1;i<=n;i++) f[i]=rd();
	}
	void solve()
	{
		
	}
	void gauss(int n)
	{
		int p;
		for (int i=1;i<=n;i++)
		{
			if (!C[i][i])
			{
				for (int j=i+1;j<=n;j++)
					if (C[j][i])
					{
						for (int k=i;k<=n;k++)
							C[i][k]=(C[i][k]+C[j][k])%mod;
						break;
					}
			}
			if (!C[i][i]) return;
			for (int j=i+1;j<=n;j++)
			{
				if (!C[i][j]) continue;
				p=1ll*C[j][i]*getinv(C[i][i])%mod;
				for (int k=i;k<=n;k++)
					C[j][k]=(C[j][k]-1ll*C[i][k]*p%mod+mod)%mod;
			}
		}
	}
	void bf()
	{
		for (int i=1;i<=n;i++) m=max(m,f[i]);
		A[1]=1;
		for (int i=1;i<=m;i++)
		{
			A[i<<1]=-A[i];
			A[i-1<<1|1]=A[i]*(i&1?1:-1);
		}
	//	for (int i=1;i<m;i++)
	//		cerr << A[i] << ' ';
	//	cerr << '\n';
		for (int i=1;i<=m;i++) B[i]=B[i-1]+A[i];
		for (int i=1;i<=n;i++) 
			for (int j=1;j<=n;j++)
				C[i][j]=B[f[__gcd(i,j)]];
		ans=1;gauss(n);
		for (int i=1;i<=n;i++)
			ans=1ll*ans*C[i][i]%mod;
		writeln(ans);
	}
	void project()
	{
		fo(sequence);
		init();
		bf();
		//solve();
	}
}

int main()
{
	MS42zz::project();
	return 0;
}



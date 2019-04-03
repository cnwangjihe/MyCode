#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200 + 10;
const int mod = 998244353;

struct edge{
	int v,n;char c;
}e[(int)(1e5)];

int n,m,an,bn,head[maxn],en=1,oud[25];
char a[15],b[55];
int nxt[15][26];

inline int Mod(int x){return x<0?x+mod:x;}
inline void MODR(int &x,int a){x+=a;if(x>=mod) x-=mod;}
inline ll qpow(ll a,ll x){ll ans=0;for(;x;x>>=1,a=a*a%mod) if(x&1) ans=ans*a%mod;return ans;}
inline void exgcd(ll a,ll b,ll &x,ll &y){if(b) exgcd(b,a%b,y,x),y-=a/b*x;else x=1,y=0;}
inline ll inv(ll a){ll x,y;exgcd(a,mod,x,y);return x<0?x+mod:x;}

void input()
{
	int i,x,y;char c;
	scanf("%d%d",&n,&m);
	for(i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);x--;y--;
		for(c=getchar();c>'z'||c<'a';c=getchar());
		e[en].v=y;e[en].c=c;e[en].n=head[x];head[x]=en++;oud[x]++;
	}
	scanf("%s%s",a,b);an=strlen(a);bn=strlen(b);
}

void pre()
{
	int i,j;
	
	static int nx[15];
	
	nx[0]=nx[1]=0;j=0;
	for(i=1;i<an;i++)
	{
		while(j && a[j]!=a[i]) j=nx[j];
		if(a[j]==a[i]) j++;
		nx[i+1]=j;
	}
	
	for(j=0;j<26;j++) nxt[0][j]=0;nxt[0][a[0]-'a']=1;
	for(i=1;i<an;i++) 
	{
		for(j=0;j<26;j++) nxt[i][j]=nxt[nx[i]][j];
		nxt[i][a[i]-'a']=i+1;
	}
}

int f[55][205];

struct Guass
{
	int a[205][205];
	
	inline void swp(int *a,int *b,int n){if(a==b) return;for(int i=0;i<=n;i++) swap(a[i],b[i]);}
	void solve(int n,int *f)
	{
		int i,j,k;
		
		for(i=0;i<n;i++)
		{
			for(j=i;j<n;j++) if(a[j][i]) swp(a[i],a[j],n);
			ll iv=Mod(-inv(a[i][i]));
			for(j=0;j<n;j++) if(j!=i && a[j][i])
			{
				ll t=a[j][i]*iv%mod;
				for(k=i;k<=n;k++) a[j][k]=(a[j][k]+t*a[i][k])%mod;
			}
		}
		for(i=0;i<n;i++) f[i]=a[i][n]*inv(a[i][i])%mod;
	}
	
	void clear(){memset(a,0,sizeof(a));}
	
	inline int *operator [](int x){return a[x];}
	
	void debug(int N)
	{
		int i,j;
		for(i=0;i<N;i++,cerr<<'\n') for(j=0;j<=N;j++) cerr << a[i][j] << ' ';cerr << '\n';
	}
}G;

inline int to(int n,int ai){return n*an+ai;}
void solve()
{
	int i,ai,j,aj,k,u,v,N=n*an;
	for(i=0;i<N;i++) f[bn][i]=0;
	cerr << N << endl;
	for(k=bn-1;~k;k--)
	{
		G.clear();
		for(i=0;i<n;i++) for(ai=0;ai<an;ai++)
		{
			u=to(i,ai);ll ivd=inv(oud[i]),mivd=Mod(-ivd); //f[i]=1/oud[x]*(f[oud]) + 1
			G[u][N]=1;G[u][u]=1;
			for(j=head[i];j;j=e[j].n)
			{
				aj=nxt[ai][e[j].c-'a'];v=to(e[j].v,aj);
				if(b[k]==e[j].c) MODR(G[u][N],(aj^an?f[k+1][v]:0)*ivd%mod),cerr << "f*k" << ai << ' ' << aj << ' ' << v << '\n' ;
				else if(aj^an) MODR(G[u][v],mivd),cerr << "f**k" << ai << ' ' << aj << ' ' << mivd << '\n';
			}
		}
		//printf("At k=%d\n",k);
	//	G.debug(N);
		G.solve(N,f[k]);
		for (int i=0;i<N;i++)
			cerr << f[k][i] << ' ';
		cerr << '\n';
	//	G.debug(N);
		return ;
	}
	printf("%d\n",f[0][0]);
}

int main()
{
//	freopen("wlk.in","r",stdin);
//	freopen("wlk.out","w",stdout);
	freopen("debug.std","w",stderr);
	
	input();
	pre();
	solve();
	
	return 0;
}

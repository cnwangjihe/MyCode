#include<bits/stdc++.h>
#define fir first
#define sec second
#define mkp make_pair
#define ppc __builtin_popcount
using namespace std;
typedef long long ll;

const int maxn = 50 + 10;

int n,w[maxn],U;
ll p2[maxn];

void pre(){for(int i=0;i<maxn;i++) p2[i]=1ll<<i;}

void input()
{
	int i,j;
	
	scanf("%d",&n);U=0;
	for(i=0;i<n;i++) scanf("%d",w+i),w[i]=~w[i]&1048575,cerr << w[i] << ' ';
	cerr << '\n';
	for(i=0;i<n;i++) U|=w[i];
	for(i=0;i<20;i++) if(U>>i&1)
	{
		for(j=0;j<n;j++) if(~w[j]>>i&1) goto fal;
		U-=1<<i;
		fal:;
	}
	cerr << U << endl;
}

struct DSU{
	int f[maxn];stack<pair<int,int> >S;
	
	DSU(){for(int i=0;i<maxn;i++) f[i]=i;}
	inline int fa(int x)
	{
		if(f[x]==x) return x;
		if(f[x]^fa(f[x])) S.push(mkp(x,f[x]));
		return f[x]=f[f[x]];
	}
	
	inline void merge(int x,int y){if(fa(x)^fa(y)) S.push(mkp(f[x],f[f[x]]));f[f[x]]=f[y];}
	inline void reset(int n){while((int)S.size()>n) f[S.top().fir]=S.top().sec,S.pop();}
	inline int cnt(){int ans=0;for(int i=0;i<n;i++) ans+=(f[i]==i);return ans;}
	inline int size(){return S.size();}
}D;

ll ans=0,cnt;
void dfs(int x)
{
	if(x==20){ans+=(cnt&1?-p2[D.cnt()]+2:p2[D.cnt()]-2);return;}

	dfs(x+1);if(~U>>x&1) return;
//	std::cerr << "### : " << x << '\n';
	cnt^=1;
	int t=D.size(),i,lst;
//	cerr << "^^^ : " << t << endl;
	for(lst=-1,i=0;i<n;i++) if(w[i]>>x&1)
	{
		if(~lst)
		{
			D.merge(lst,i);
//			cerr << "$$$ : " << lst << ' ' << i << '\n';
		}
		lst=i;
	}
	dfs(x+1);
	cnt^=1;D.reset(t);
//	cerr << "*** : back\n";
}

void solve()
{
	ans=0;dfs(0);
	printf("%lld\n",ans);
}

int main()
{
//	freopen("2733.in","r",stdin);
//	freopen("2733.out","w",stdout);
	
	pre();
	int tt;
	scanf("%d",&tt);
	while(tt--)
	{
		input();
		solve();
	}
	
	return 0;
}

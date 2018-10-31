#include <bits/stdc++.h>
#define ft(i,a,b) for(int i=(a); i<=(b); ++i)
#define fd(i,a,b) for(int i=(a); i>=(b); --i)
using namespace std;
typedef long long LL;

const int N=100050;

LL a[N],g[N];
int r[N],top;

void solve(){
	int n; scanf("%d",&n);
	ft(i,1,n) scanf("%lld",&a[i]);
	top=0; LL ans=0;
	fd(i,n,1){
		ft(j,1,top) g[j]=__gcd(g[j],a[i]);
		top++; g[top]=a[i]; r[top]=i;
		int t=1;
		ft(j,2,top) if (g[j]!=g[t]){
			t++; g[t]=g[j]; r[t]=r[j];
		}
		top=t;
		ft(j,1,top) ans=max(ans,1ll*g[j]*(r[j]-i+1));
	}
	printf("%lld\n",ans);
}

int main(){
//	freopen("2687.in","r",stdin);
//	freopen("2687.out","w",stdout);
	int t; scanf("%d",&t);
	while (t--) solve();
	return 0;
}




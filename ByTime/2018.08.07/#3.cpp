#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;

const int N=500050;

bool b[N];
int a[N],cnt,mx[N],mu[N];

void getprime(int n=500000){
	forto(i,2,n) b[i]=true;
	mu[1]=1;
	forto(i,2,n){
		if (b[i]){
			a[++cnt]=i;
			mx[i]=cnt;
			mu[i]=-1;
		}
		forto(j,1,mx[i]){
			int k=i*a[j];
			if (k>n) break;
			b[k] = false;
			mx[k] = j;
			mu[k] = j==mx[i] ? 0 : -mu[i];
		}
	}
}

int s[N];

int main(){
///     freopen("2591.in", "r", stdin);
///     freopen("2591.out","w",stdout);
	getprime();
	forto(i,1,20) printf("mu[%d]=%d\n",i,mu[i]);
	int n; scanf("%d",&n);
	forto(d,1,n){
		int t=mu[d]*(n/d);
		for(int i=d; i<=n; i+=d) s[i]+=t;
	}
	s[1]--;
	//forto(i,1,n) printf("%d\n",s[i]); 
	LL sum=0;
	forto(i,1,n) sum+=1ll*s[i]*(n-1-s[i]);
	LL ans = LL(n)*(n-1)*(n-2)/6 - sum/2;
	printf("%lld\n",ans);
	return 0;
}
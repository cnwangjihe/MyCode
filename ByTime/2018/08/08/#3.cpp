#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
typedef long long LL;

const int N=5000000;
const int P=100000007;

bool b[N+10];
int a[N+10],cnt,mx[N+10];

void getprime(){
	forto(i,2,N) b[i]=true;
	forto(i,2,N){
		if (b[i]){
			a[++cnt]=i;
			mx[i]=cnt;
		}
		for(int j=1; j<=mx[i] && i*a[j]<=N; j++){
			int k = i*a[j];
			b[k]=false; mx[k]=j;
		}
	}
}

int solve(int x){
	LL ans=1;
	for(int i=1; a[i]<=x && i<=cnt; i++){
		LL sum=1;
		for(LL t=a[i]; t<=x; t*=a[i]){
			LL f=(x-t+1);
			LL s=x/t;
			LL m=f-(s-1)*t;
			sum+=(f+m)*s/2;
			sum%=P;
			//if (x==4 && t==2) printf("sum=%lld\n",sum);
			//printf("%d %lld\n",a[i],sum);
		}
		//printf("%d %lld\n",a[i],sum);
		ans=ans*sum%P;
	}
	return ans;
}		

int main(){
	freopen("2595.in","r",stdin);
	freopen("2595.out","w",stdout);
	getprime();
	while (true){
		int x; scanf("%d",&x);
		if (x==0) return 0;
		printf("%d\n",solve(x));
	}
	return 0;
}
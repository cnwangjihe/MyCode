//   Author:Arturia
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<ctime>
#include<cstdlib>
#include<string>
#include<queue>
#include<cmath>
#include<set>
#include<map>
#include<bitset>
#include<vector>
#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
#define VS vector<string>
using namespace std;
inline ll rd(){
	ll x=0;int ch=getchar(),f=1;
	while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
	if (ch=='-'){f=-1;ch=getchar();}
	while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline void rt(ll x){
	if (x<0) putchar('-'),x=-x;
	if (x>=10) rt(x/10),putchar(x%10+'0');
		else putchar(x+'0');
}
const int maxn=405;
pair<ll,ll>ans[maxn];
int cnt;
ll a,b,c,g;
void get(ll a,ll b){
	ans[++cnt]=mk(a,b);
}
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
void solve(ll a,ll b,ll t){//have a&b,get a-b*t
	if (!t) return;
	get(a,b);
	ll la=a-b,lb=b,pw=2;
	while (pw<=t){
		get(la,lb);la-=lb;		//get a-pw*b
		if (pw*2<=t) get(a,la);	//get pw*b
		lb<<=1,pw<<=1;			//la=a-pw*b,lb=pw*b
	}
	pw>>=1;t-=pw;pw>>=1;
	for (;t;pw>>=1) if (t>=pw) get(la,b*pw),la-=b*pw,t-=pw;
}
ll getgcd(ll a,ll b){
	if (b>a) swap(a,b);
	if (a%b==0) return b;
	ll t=a/b;
	solve(a,b,t);
	getgcd(b,a%b);
}
int main(){
	a=rd(),b=rd(),c=rd();
	if (b>a) swap(a,b);
	if (c>a||c%gcd(a,b)) return puts("-1"),0;
	g=getgcd(a,b);
	solve(a,g,(a-c)/g);
	while (cnt>0&&ans[cnt].fs-ans[cnt].sc!=c) cnt--;
	printf("%d\n",cnt);
	rep(i,1,cnt) printf("%lld %lld\n",ans[i].fs,ans[i].sc);
}

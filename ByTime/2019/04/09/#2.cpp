#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=='-'?f=-1:0,ch=getchar());
    for(;isdigit(ch);x=x*10+ch-'0',ch=getchar());
    return x*f;
}
ll n,m,k[100005],tot,p[100005],mx[100005],ans=1,sum;
char s[200005];
int main(){
	freopen("queue.in","r",stdin);
//	freopen("queue.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;++i){
		scanf("%s",s+1);k[i]=read();
		int len=strlen(s+1);
		for(int j=len;j;--j)p[i]+=s[j]=='F'?-1:1,mx[i]=max(mx[i],p[i]);
		tot+=p[i]*k[i];
	}
	if(tot>0){puts("-1");return 0;}
	for(int i=m;i;--i){
		if(p[i]>0)ans=max(ans,sum+(k[i]-1)*p[i]+mx[i]);
		else ans=max(ans,sum+mx[i]);
		sum+=k[i]*p[i];
	}
	printf("%lld\n",ans-1);
} 
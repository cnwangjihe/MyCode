#include<bits/stdc++.h>
#define mkp make_pair
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair<ll,int> pii;
const int N=4e6+10;
int n,K,top,pre[N],nex[N];
bool fg[N];
ll ans,a[N],b[N];
priority_queue<pii>q;
char nc() 
{
    static char ch[100000],*s=ch,*t=ch;
    return s==t&&(t=(s=ch)+fread(ch,1,100000,stdin),s==t)?-1:*s++;
}
ll read()
{
	ll ret=0;char c=nc();
	while(!isdigit(c)) c=nc();
	while(isdigit(c)) ret=ret*10+(c^48),c=nc();
	return ret;
}

void init()
{
	n=read();K=read();
	for(int i=1;i<=n;++i) a[i]=read(); --n;
	for(int i=1;i<=n;++i)
	{
		a[i]=a[i+1]-a[i];
		if(a[i]>0) {ans+=a[i];if(b[top]>0) b[top]+=a[i]; else b[++top]=a[i];}
		else{if(b[top]<=0) b[top]+=a[i]; else b[++top]=a[i];}
	}
	if(b[top]<=0) --top;
	n=top;
}
void solve()
{
	if((n+1)>>1<=K){printf("%lld\n",ans);exit(0);}
	K=((n+1)>>1)-K;
	for(int i=1;i<=n;++i) b[i]=abs(b[i]),q.push(mkp(-b[i],i)),pre[i]=i-1,nex[i]=(i<n)?(i+1):0;
	while(K--)
	{
		while(fg[q.top().se]) q.pop();
		int x=q.top().se;ans+=q.top().fi;q.pop();
		int u=pre[x],v=nex[x];fg[u]=fg[v]=1;
		if(u && v)
		{
			pre[x]=pre[u];nex[x]=nex[v];
			if(pre[x]) nex[pre[x]]=x;
			if(nex[x]) pre[nex[x]]=x;
			b[x]=b[u]+b[v]-b[x];q.push(mkp(-b[x],x));
		}
		else
		{
			pre[x]=pre[u];nex[x]=nex[v];
			if(pre[x]) nex[pre[x]]=nex[x];
			if(nex[x]) pre[nex[x]]=pre[x];
			fg[x]=1;
		}
	}
	printf("%lld\n",ans);
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	init();solve();
	return 0;
}

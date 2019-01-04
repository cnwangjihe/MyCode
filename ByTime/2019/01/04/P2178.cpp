// Date      : 2019-01-04 08:01:42
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P2178
// Algorithm : SA,RMQ,单调栈
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long) - __builtin_clzl((X)) - 1))

const int ALPHABET_SET_SIZE = 26;
const int MAXN = 300009,
		  MAXK = 20;
const long long INF = 2000000000000000009ll;

struct RMQ
{
	int Min[MAXK][MAXN],Max[MAXK][MAXN];
	RMQ(){};
	void Build(int *a,int n)
	{
		int k=LOG2(n);
		for (int i=0;i<n;i++)
			Min[0][i]=Max[0][i]=a[i];
		for (int i=1;i<=k;i++)
			for (int j=0;j<n;j++)
				if (j+(1<<i)-1<n)
				{
					Min[i][j]=min(Min[i-1][j],Min[i-1][j+(1<<(i-1))]);
					Max[i][j]=max(Max[i-1][j],Max[i-1][j+(1<<(i-1))]);
				}
		return ;
	}
	int QueryMin(int l,int r)
	{
		int k=LOG2(r-l+1);
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
	int QueryMax(int l,int r)
	{
		int k=LOG2(r-l+1);
		return max(Max[k][l],Max[k][r-(1<<k)+1]);
	}
};

RMQ RMQ;
int rank[MAXN],sa[MAXN],tmp[MAXN],cnt[MAXN];
int s[MAXN],h[MAXN],v[MAXN];
int upcnt[MAXN],upmin[MAXN],upmax[MAXN];
long long sum[MAXN],ans[MAXN];
int stack[MAXN];
int n,top;


inline bool _cmp(int *r,int a,int b,int len) {return (r[a]==r[b] && r[a+len]==r[b+len]);}

void _getrank(int *rank,int *sa,int *tmp,int n,int m)
{
	for (int i=0;i<m;i++) cnt[i]=0;
	for (int i=0;i<n;i++) cnt[rank[i]]++;
	for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for (int i=n-1;~i;i--) sa[--cnt[rank[i]]]=i;
	for (int j=1,p=1;p<n;m=p,j*=2)
	{
		p=0;
		for (int i=n-j;i<n;i++) tmp[p++]=i;
		for (int i=0;i<n;i++) if (sa[i]>=j) tmp[p++]=sa[i]-j;
		for (int i=0;i<m;i++) cnt[i]=0;
		for (int i=0;i<n;i++) cnt[rank[tmp[i]]]++;
		for (int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for (int i=n-1;~i;i--) sa[--cnt[rank[tmp[i]]]]=tmp[i];
		for (int i=0;i<n;i++) swap(tmp[i],rank[i]);
		rank[sa[0]]=0;
		p=1;
		for (int i=1;i<n;i++)
			rank[sa[i]]=_cmp(tmp,sa[i-1],sa[i],j)?p-1:p++;
	}
	return ;
}
	
void _getheight(int *rank,int *sa,int *height,int *s,int n)
{
	int x=0,j;
	for (int i=0;i<n;i++)
	{
		x-=(x>0);
		if (!rank[i])
			continue;
		j=sa[rank[i]-1];
		while (s[i+x]==s[j+x])
			x++;
		height[rank[i]]=x;
	}
	return ;
}

void solve()
{
	int u;
	for (int i=1;i<=n;i++)
	{
		upcnt[i]=1;
		upmax[i]=upmin[i]=v[i-1];
		while (top && h[i]<=h[stack[top]])
		{
			u=stack[top--];
			sum[h[u]]+=1ll*upcnt[u]*(i-u);
			ans[h[u]]=max(ans[h[u]] , max(1ll*upmax[u]*RMQ.QueryMax(u,i-1) , 1ll*upmin[u]*RMQ.QueryMin(u,i-1)));
			upmax[i]=max(upmax[i],upmax[u]);
			upmin[i]=min(upmin[i],upmin[u]);
			upcnt[i]+=upcnt[u];
		}
		stack[++top]=i;
	}
	return ;
}

int main()
{
//	freopen("P2178.in","r",stdin);
//	freopen("P2178.out","w",stdout);
	int t;
	n=0;
	do {s[0]=getchar()-'a';}
		while (s[0]<0 || s[0]>25);
	do {s[++n]=getchar()-'a';}
		while (s[n]>=0 && s[n]<=25);

	fill(s+n,s+MAXN,-1);
	copy(s+0,s+MAXN,rank+0);
	fill(tmp+0,tmp+MAXN,-1);
	_getrank(rank,sa,tmp,n,ALPHABET_SET_SIZE);
	_getheight(rank,sa,h,s,n);

	for (int i=0;i<n;i++)
		scanf("%d",&t),v[rank[i]]=t;
	RMQ.Build(v,n);

	fill(ans+0,ans+MAXN,-INF);
	solve();

	for (int i=n-2;~i;i--)
		sum[i]+=sum[i+1],ans[i]=max(ans[i],ans[i+1]);
	for (int i=0;i<n;i++)
		printf("%lld %lld\n",sum[i],(ans[i]==-INF)?0:ans[i]);
	return 0;
}
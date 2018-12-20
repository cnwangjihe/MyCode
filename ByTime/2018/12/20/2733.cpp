// Date    : 2018-12-20 09:48:10
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 52,
		  MAXK = 20;

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1))

struct UFset
{
	int fa[MAXN],top;
	int x[MAXN*MAXN],y[MAXN*MAXN];
	UFset()
	{
		top=0;
		for (int i=0;i<MAXN;i++)
			fa[i]=i;
	}
	inline void record(int a,int b) {x[top]=a,y[top]=b,top++;}
	inline void back() {top--,fa[x[top]]=y[top];}
	int find(int u)
	{
		if (fa[u]==u)
			return u;
		if (fa[u]!=find(fa[u]))
			record(u,fa[u]);
		return fa[u]=fa[fa[u]];
	}
	inline bool merge(int a,int b)
	{
		if (find(a)==find(b))
			return 0;
		record(fa[a],fa[fa[a]]);
		fa[fa[a]]=fa[b];
		return 1;
	}
	inline void rollback(int k)
	{
		while (top>k)
			back();
		return ;
	}
};

UFset U;
int a[MAXN];
long long v[MAXK];
int sum1,sum2,sum;
int n;
long long ans;

void dfs(int k,int minus,int cnt)
{
	if (k==MAXK)
	{
		ans+=1ll*minus*((1ll<<(n-cnt))-2);
		return ;
	}
	dfs(k+1,minus,cnt);
	if (!((1<<k)&sum))
		return ;
	static int i,j;
	static long long t;
	int beforec=U.top;
	for (t=v[k],j=LOG2(t&-t),i=-1;t;t^=t&-t,i=j,j=LOG2(t&-t))
		if (~i)
			cnt+=U.merge(i,j);
	dfs(k+1,minus*-1,cnt);
	U.rollback(beforec);
	return ;
}

int main()
{
	freopen("2733.in","r",stdin);
	freopen("2733.out","w",stdout);
//	int tcounter=clock();
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		memset(v,0,sizeof v);
		ans=0;
		scanf("%d",&n);
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			sum1=(!i)?a[i]:sum1&a[i];
			sum2=(!i)?a[i]:sum2|a[i];
		}
		sum=~(~sum2|sum1);
		for (int i=0;i<MAXK;i++)
		{
			if (!(sum&(1<<i)))
				continue;
			for (int j=0;j<n;j++)
				if (!(a[j]&(1<<i)))
					v[i]|=(1ll<<j);
		}
		dfs(0,1,0);
		printf("%lld\n",ans);
	}
	return 0;
}
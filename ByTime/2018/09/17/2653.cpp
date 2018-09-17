#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MOD  = 1000000007;

struct Tnode
{
	int v,l,r;
	void clear(){v=l=r=0;}
	Tnode(){clear();}
};

int pos[MAXN],size[MAXN];
int a[MAXN],inv[MAXN];
int n,ans,fp,root;
Tnode t[MAXN];

inline void clear(int n)
{
	fp=root=0;
	ans=1ll*n*inv[2]%MOD;
	for (int i=0;i<=n+1;i++)
		t[i].clear(),size[i]=0,pos[i]=0;
	return ;
}

void build(int &root)
{
	int last=0,p=0;
	for (int i=1;i<=n;i++)
	{
		while (p && t[pos[p]].v<a[i])
			last=pos[p--];
		t[++fp].v=a[i];
		if (!p)
			root=fp;
		else
			t[pos[p]].r=fp;
		t[fp].l=last;
		pos[++p]=fp;
		last=0;
	}
	return ;
}

int dfs(int u)
{
	size[u]=1;
	if (t[u].l)
		size[u]+=dfs(t[u].l);
	if (t[u].r)
		size[u]+=dfs(t[u].r);
	return size[u];
}

inline int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if ((1<<i)&k)
			ans=1ll*ans*a%MOD;
	return ans;
}

int main()
{
	freopen("2653.in","r",stdin);
	freopen("2653.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int i=1;i<MAXN;i++)
		inv[i]=qpow(i,MOD-2);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%d",&n);
		clear(n);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		build(root);
	//	cerr << "Step 1 done!\n";
		dfs(root);
	//	cerr << "Step 2 done!\n";
		for (int i=1;i<=n;i++)
			ans=1ll*ans*inv[size[i]]%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
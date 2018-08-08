#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009,
		  MAXM = 100009;

struct Tquery{int l,r,i,t;};

Tquery q[MAXM];
int dep[MAXN],a[MAXN*2],e[MAXN],s[MAXN];
int f[MAXN][18];
int _next[MAXN*2],_node[MAXN*2],_head[MAXN];
int fp=0,n,m,k=0,tot,d;
int ext[MAXN],lca[MAXM];
int v[MAXN],ans[MAXM];
int cnt[MAXN],b[MAXN],p[MAXN];

void _connect(int a,int b)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_head[a]=fp++;
	return ;
}

void dfs(int u,int fa)
{
	int v;
	dep[u]=dep[fa]+1;
	s[u]=k;
	a[k++]=u;
	f[u][0]=fa;
	for (int i=1;f[u][i-1];i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa)
			continue;
		dfs(v,u);
	}
	e[u]=k;
	a[k++]=u;
	return ;
}

int getlca(int a,int b)
{
	if (dep[b]>dep[a])
		swap(a,b);
	int d=dep[a]-dep[b];
	for (int i=16;~i;i--)
		if (d&(1<<i))
			a=f[a][i];
//	cerr << a << ' ' << b << "sdfsd \n";
	if (a==b)
		return a;
	for (int i=16;~i;i--)
		if (f[a][i]!=f[b][i])
			a=f[a][i],b=f[b][i];
	return f[a][0];
}

bool _cmpl(Tquery a,Tquery b) {return a.l<b.l;}
bool _cmpr(Tquery a,Tquery b) {return a.r<b.r;}
bool _cmp(int x,int y) {return b[x]<b[y];}

inline void _update(int i)
{
	ext[i]^=1;
	if (ext[i])
	{
		if (cnt[v[i]]==0)
			tot++;
		cnt[v[i]]++;
	}
	else
	{
		cnt[v[i]]--;
		if (cnt[v[i]]==0)
			tot--;
	}
	return ;
}

int main()
{
	int x,y;
	memset(_head,-1,sizeof _head);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&b[i]),p[i]=i;
	sort(p+1,p+1+n,_cmp);
	int t=0;
	for (int i=1;i<=n;i++)
	{
		while (i+1<=n && b[p[i]]==b[p[i+1]])
			v[p[i++]]=t;
		v[p[i]]=t++;
	}
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		_connect(x,y);
		_connect(y,x);
	}
	dfs(1,0);
//	cerr << dep[3] << ' ' << dep[5] << ' ' << f[5][0] << ' ' << getlca(3,5) << " sdf\n";
//	for (int i=0;i<k;i++)
//		cerr << a[i] <<' ';
//	cerr << '\n';
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		if (s[x]>s[y])
			swap(x,y);
		lca[i]=getlca(x,y);
		if (lca[i]==x)
			q[i].l=s[x],q[i].r=s[y],q[i].i=i,q[i].t=0;
		else
			q[i].l=e[x],q[i].r=s[y],q[i].i=i,q[i].t=1;
//		cerr << lca[i] << ' ' << q[i].l << ' ' << q[i].r << '\n';
	}
	sort(q,q+m,_cmpl);
	d=sqrt(k);
	int r,al=0,ar=0;
	for (int l=0;l<k && ar<m;l+=d)
	{
		r=l+d;
		al=ar;
		while (q[ar].l<r && ar<m)
			ar++;
	//	cerr << l << ' ' << r << ' ' << al << ' ' << ar << endl;
		if (al==ar)
			continue;
		sort(q+al,q+ar,_cmpr);
		memset(cnt,0,sizeof cnt);
		tot=0;
		memset(ext,0,sizeof ext);
		for (int i=q[al].l;i<=q[al].r;i++)
			_update(a[i]);
		if  (q[al].t)
		{
			_update(lca[q[al].i]);
			ans[q[al].i]=tot;
			_update(lca[q[al].i]);
		}
		else
			ans[q[al].i]=tot;
		for (int i=al+1;i<ar;i++)
		{
			for (int j=min(q[i-1].r+1,q[i].r+1);j<=max(q[i-1].r,q[i].r);j++)
				_update(a[j]);
			for (int j=min(q[i-1].l,q[i].l);j<=max(q[i-1].l-1,q[i].l-1);j++)
				_update(a[j]);
			if (q[i].t)
			{
				_update(lca[q[i].i]);
				ans[q[i].i]=tot;
				_update(lca[q[i].i]);
			}
			else
				ans[q[i].i]=tot;
		}
	}
	for (int i=0;i<m;i++)
		printf("%d\n",ans[i]);
	return 0;
}

/* 1223556677348841 */
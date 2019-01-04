// Date      : 2019-01-03 19:05:55
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P4094
// Algorithm : SA,可持久化线段树,RMQ,二分
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long) - __builtin_clzl((X)) - 1))

const int ALPHAPET_SET_SIZE = 26; 
const int MAXN = 100009,
		  MAXK = 19,
		  INF  = 2000000009;

struct PersistentSegmentTree
{
	struct SegmentTreeNode
	{
		int v,lc,rc;
		void Clear(){v=lc=rc=0;}
		SegmentTreeNode(){Clear();}
	};
	struct NodePool
	{
		SegmentTreeNode node[MAXN*MAXK];
		int Stack[MAXN*MAXK],top,fp;
		NodePool(){top=0,fp=1;}
		SegmentTreeNode& operator[](int u) {return node[u];}
		int New(int u=0)
		{
			int v=top?Stack[--top]:fp++;
			node[v]=node[u];
			return v;
		}
		inline void Free(int u) {Stack[top++]=u;}
	};
	NodePool t; 
	inline void Up(int u) {t[u].v=t[t[u].lc].v+t[t[u].rc].v;}
	void Insert(int &u,int l,int r,int p,int v)
	{
		u=t.New(u);
		if (l==r)
		{
			t[u].v+=v;
			return ;
		}
		int mid=(l+r)>>1;
		if (p<=mid)
			Insert(t[u].lc,l,mid,p,v);
		else
			Insert(t[u].rc,mid+1,r,p,v);
		Up(u);
	}
	int Query(int u,int l,int r,int al,int ar)
	{
		if (!u)
			return 0;
		if (al<=l && ar>=r)
			return t[u].v;
		int mid=(l+r)>>1,sum=0;
		if (al<=mid)
			sum+=Query(t[u].lc,l,mid,al,ar);
		if (ar>mid)
			sum+=Query(t[u].rc,mid+1,r,al,ar);
		return sum;
	}
};

struct RMQ
{
	int Min[MAXK][MAXN];
	RMQ(){}
	void Build(int *a,int n)
	{
		int k=LOG2(n);
		for (int i=0;i<n;i++)
			Min[0][i]=a[i];
		for (int i=1;i<=k;i++)
			for (int j=0;j<n;j++)
				if (j+(1<<i)-1<n)
					Min[i][j]=min(Min[i-1][j],Min[i-1][j+(1<<(i-1))]);
		return ;
	}
	int Query(int l,int r)
	{
		if (l>r)
			return INF;
		int k=LOG2(r-l+1);
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
};

RMQ RMQ;
PersistentSegmentTree PST;
int n,m;
int cnt[MAXN],rank[MAXN],sa[MAXN],h[MAXN],tmp[MAXN];
int root[MAXN];
int s[MAXN];

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

bool check(int v,int p,int al,int ar)
{
	int upside,downside;
	int l=-1,r=p+1,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (RMQ.Query(mid+1,p)>=v)
			r=mid;
		else
			l=mid;
	}
	if (r==p+1)
		return 0;
	upside=r;
	l=p-1,r=n;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if (RMQ.Query(p+1,mid)>=v)
			l=mid;
		else
			r=mid;
	}
	if (l==p-1)
		return 0;
	downside=l;
//	cerr << "&&& : " << al << ' ' << ar << ' ' << upside << ' ' << downside << '\n';
	return PST.Query(root[downside+1],1,n,al+1,ar+1)-PST.Query(root[upside],1,n,al+1,ar+1);
}

int main()
{
//	freopen("P4094.in","r",stdin);
//	freopen("P4094.out","w",stdout);
	int a,b,c,d;
	scanf("%d%d",&n,&m);
	n=0;
	do {s[0]=getchar()-'a';}
		while (s[0]<0 || s[0]>25);
	do {s[++n]=getchar()-'a';}
		while (s[n]>=0 && s[n]<=25);
	fill(s+n,s+MAXN,-1);
	fill(tmp+0,tmp+MAXN,-1);
	copy(s+0,s+MAXN,rank+0);
	_getrank(rank,sa,tmp,n,ALPHAPET_SET_SIZE);
	_getheight(rank,sa,h,s,n);
	RMQ.Build(h,n);
	for (int i=0;i<n;i++)
		PST.Insert(root[i+1]=root[i],1,n,sa[i]+1,1);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		a--,b--,c--,d--;
		int l=0,r=min(b-a+1,d-c+1)+1,mid;
		while (l+1<r)
		{
			mid=(l+r)>>1;
			if (check(mid,rank[c],a,b-mid+1))
				l=mid;
			else
				r=mid;
		}
		printf("%d\n",l);
	}
	return 0;
}
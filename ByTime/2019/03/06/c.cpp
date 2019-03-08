// Date      : 2019-03-06 09:21:55
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009,
		  MOD  = 1000000007;

struct Tnum{int v,i;};

inline int Add(int a,int b) {a+=b;return a>MOD?a-MOD:(a<0?a+MOD:a);}
inline int Mul(int a,int b) {return 1ll*a*b%MOD;}

struct SegmentTree
{
	struct Tnode{int v,d;inline void clear(){v=d=0;}Tnode(){clear();}};
	Tnode t[MAXN*4];
	inline void Clear()
	{
		for (int i=0;i<MAXN*4;i++)
			t[i].clear();
		return ;
	}
	inline void Down(int u,int l,int r)
	{
		if (!t[u].d)
			return ;
		int mid=(l+r)>>1;
		t[u*2].d=Add(t[u*2].d,t[u].d);
		t[u*2+1].d=Add(t[u*2+1].d,t[u].d);
		t[u*2].v=Add(t[u*2].v,Mul(t[u].d,mid-l+1));
		t[u*2+1].v=Add(t[u*2+1].v,Mul(t[u].d,r-mid));
		t[u].d=0;
		return ;
	}
	inline void Up(int u) {t[u].v=Add(t[u*2].v,t[u*2+1].v);}
	int Query(int u,int l,int r,int al,int ar)
	{
		if (al<=l && ar>=r)
			return t[u].v;
		Down(u,l,r);
		int mid=(l+r)>>1,ans=0;
		if (al<=mid)
			ans=Add(ans,Query(u*2,l,mid,al,ar));
		if (ar>mid)
			ans=Add(ans,Query(u*2+1,mid+1,r,al,ar));
		return ans;
	}
	void Modify(int u,int l,int r,int al,int ar)
	{
		if (al<=l && ar>=r)
		{
			t[u].d=Add(t[u].d,1);
			t[u].v=Add(t[u].v,r-l+1);
			return ;
		}
		Down(u,l,r);
		int mid=(l+r)>>1;
		if (al<=mid)
			Modify(u*2,l,mid,al,ar);
		if (ar>mid)
			Modify(u*2+1,mid+1,r,al,ar);
		Up(u);
		return ;
	}
};

SegmentTree ST;
int n,cnt,ans=0;
Tnum a[MAXN];

bool _cmp(Tnum a,Tnum b) {return a.v<b.v;}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i].v),a[i].i=i;
	sort(a+1,a+1+n,_cmp);
	for (int i=1;i<=n;i++)
	{
		cnt=Add(ST.Query(1,1,n,1,a[i].i),-Mul(Add(ST.Query(1,1,n,a[i].i,a[i].i),-1),a[i].i));
		cnt=Mul(cnt,n-a[i].i+1);
		ans=Add(ans,Mul(a[i].v,cnt));
		ST.Modify(1,1,n,1,a[i].i);
	}
	ST.Clear();
	for (int i=1;i<=n;i++)
	{
		cnt=Add(ST.Query(1,1,n,a[i].i+1,n),-Mul(ST.Query(1,1,n,a[i].i,a[i].i),n-a[i].i));
		cnt=Mul(cnt,a[i].i);
		ans=Add(ans,Mul(a[i].v,cnt));
		ST.Modify(1,1,n,a[i].i,n);
	}
	printf("%d\n",ans);

	return 0;
}
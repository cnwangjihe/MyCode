// Date    : 2018-12-17 18:06:18
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tnode
{
	long long s[3],add;
	Tnode(){memset(s,0,sizeof s);add=0;}
	Tnode& operator += (const Tnode &a)
	{
		for (int i=0;i<3;i++)
			this->s[i]+=a.s[i];
		this->add=0;
		return *this;
	}
	friend Tnode operator + (Tnode a,const Tnode& b)
	{
		a+=b;
		return a;
	}
};

Tnode t[MAXN*4];
long long c[3][MAXN];
int n,m;

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

inline long long _calcadd(int t,long long v,int l,int r){return (c[t][r]-c[t][l-1])*v;}

inline void _up(int u){t[u]=t[u*2]+t[u*2+1];}

void _down(int u,int l,int r)
{
	if (t[u].add==0)
		return ;
	int mid=(l+r)>>1;
	t[u*2].add+=t[u].add;
	t[u*2+1].add+=t[u].add;
	for (int i=0;i<3;i++)
		t[u*2].s[i]+=_calcadd(i,t[u].add,l,mid),
		t[u*2+1].s[i]+=_calcadd(i,t[u].add,mid+1,r);
	t[u].add=0;
	return ;
}

void _modify(int u,int l,int r,int al,int ar,int v)
{
	if (al<=l && ar>=r)
	{
		t[u].add+=v;
		for (int i=0;i<3;i++)
			t[u].s[i]+=_calcadd(i,v,l,r);
		return ;
	}
	_down(u,l,r);
	int mid=(l+r)>>1;
	if (al<=mid)
		_modify(u*2,l,mid,al,ar,v);
	if (ar>mid)
		_modify(u*2+1,mid+1,r,al,ar,v);
	_up(u);
	return ;
}

Tnode _query(int u,int l,int r,int al,int ar)
{
	if (al<=l && ar>=r)
		return t[u];
	_down(u,l,r);
	int mid=(l+r)>>1;
	Tnode ans;
	if (al<=mid)
		ans+=_query(u*2,l,mid,al,ar);
	if (ar>mid)
		ans+=_query(u*2+1,mid+1,r,al,ar);
	return ans;
}

inline long long _calcans(Tnode a,int l,int r){return a.s[0]*(r+1)*(1-l)+a.s[1]*(r+l)-a.s[2];}

int main()
{
//	freopen("P2221.in","r",stdin);
//	freopen("P2221.out","w",stdout);
	int l,r;
	long long t1,t2,t3;
	char ch;
	n=read(),m=read();
	c[0][0]=c[1][0]=c[2][0]=0;
	for (int i=1;i<=n;i++)
	{
		c[0][i]=c[0][i-1]+1ll;
		c[1][i]=c[1][i-1]+1ll*i;
		c[2][i]=c[2][i-1]+1ll*i*i;
	}
	for (int i=0;i<m;i++)
	{
		do {ch=getchar();}
			while (ch!='C' && ch!='Q');
		l=read(),r=read()-1;
		if (ch=='C')
			_modify(1,1,n-1,l,r,read());
		else
		{
			t1=_calcans(_query(1,1,n-1,l,r),l,r);
			t2=1ll*(r-l+2)*(r-l+1)/2;
			t3=__gcd(t1,t2);
			printf("%lld/%lld\n",t1/t3,t2/t3);
		}
	}
	return 0;
}
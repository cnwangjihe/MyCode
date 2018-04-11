#include<bits/stdc++.h>
#define lc p<<1
#define rc p<<1|1
#define mid tl+tr>>1
using namespace std;

const int maxn = 2e+5 + 10;

int n,m;

struct node{
	int t1,t0,mx,dif;
	node(){t1=t0=mx=dif=0;}
	void c1(int d){mx|=d; t1|=d;t0&=~d;}
	void c0(int d){mx&=~d;t0|=d;t1&=~d;}
};
struct Segmenttree{
	node nt[maxn<<2];
	int l,r,d,typ;
	
	void up(int p)
	{
		nt[p].dif=nt[lc].mx^nt[rc].mx;
		nt[p].dif|=nt[lc].dif|nt[rc].dif;
		nt[p].mx=max(nt[lc].mx,nt[rc].mx);
	}
	
	void down(int p)
	{
		if(nt[p].t1)
		{
			nt[lc].c1(nt[p].t1);nt[rc].c1(nt[p].t1);
			nt[p].t1=0;
		}
		if(nt[p].t0)
		{
			nt[lc].c0(nt[p].t0);nt[rc].c0(nt[p].t0);
			nt[p].t0=0;
		}
	}
	
	void cha(int p,int tl,int tr)
	{
		if(l<=tl && tr<=r && !(d&nt[p].dif))
		{
			typ?nt[p].c1(d):nt[p].c0(d);
			return;
		}
		
		down(p);
		if(l<mid) cha(lc,tl,mid);
		if(mid<r) cha(rc,mid,tr);
		up(p);
	}
	
	int mx(int p,int tl,int tr)
	{
		if(l<=tl && tr<=r) return nt[p].mx;
		
		down(p);
		if(l<mid && mid<r) return max(mx(lc,tl,mid),mx(rc,mid,tr));
		if(l<mid) return mx(lc,tl,mid);
		if(mid<r) return mx(rc,mid,tr);
	}
}T;

inline int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	return x;
}

void input()
{
	int i;
	
	n=read();m=read();
	for(i=1;i<=n;i++)
	{
		T.d=read();T.l=i;T.r=i+1;T.typ=1;
		T.cha(1,0,maxn);
	}
}

void solve()
{
	int c=read();
	
	T.l=read();T.r=read()+1;
	if(c==1)
	{
		T.d=~read();T.typ=0;
		T.cha(1,0,maxn);
	}
	if(c==2)
	{
		T.d=read();T.typ=1;
		T.cha(1,0,maxn);
	}
	if(c==3)
	{
		printf("%d\n",T.mx(1,0,maxn));
	}
	//cerr<<m<<endl;
}

int main()
{
	char inp[20],oup[20];
	freopen("msg.txt","r",stdin);
	cin>>inp>>oup;
	freopen(inp,"r",stdin);
	freopen(oup,"w",stdout);
	
	input();
	while(m--) solve();
	
	return 0;
}

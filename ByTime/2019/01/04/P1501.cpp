// Date      : 2019-01-04 14:32:16
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P1501
// Algorithm : LCT,Splay
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 100009,
		  MOD  = 51061;

struct LinkCutTree
{
	int C[MAXN][2];
	int rev[MAXN];
	int fa[MAXN],cnt[MAXN];
	int val[MAXN],sum[MAXN],add[MAXN],mul[MAXN];
	void clear()
	{
		fill(mul+1,mul+MAXN,1);
	}
	LinkCutTree(){}
	bool Child(int u) {return C[fa[u]][1]==u;}
	bool isroot(int u) {return (C[fa[u]][0]!=u && C[fa[u]][1]!=u);}
	void Down(int u)
	{
		if (rev[u])
		{
			rev[C[u][0]]^=1;
			rev[C[u][1]]^=1;
			rev[u]=0;
			swap(C[u][0],C[u][1]);
		}
		if (mul[u]!=1)
		{
			val[C[u][0]]=1ll*val[C[u][0]]*mul[u]%MOD;
			add[C[u][0]]=1ll*add[C[u][0]]*mul[u]%MOD;
			sum[C[u][0]]=1ll*sum[C[u][0]]*mul[u]%MOD;
			mul[C[u][0]]=1ll*mul[C[u][0]]*mul[u]%MOD;
			val[C[u][1]]=1ll*val[C[u][1]]*mul[u]%MOD;
			add[C[u][1]]=1ll*add[C[u][1]]*mul[u]%MOD;
			sum[C[u][1]]=1ll*sum[C[u][1]]*mul[u]%MOD;
			mul[C[u][1]]=1ll*mul[C[u][1]]*mul[u]%MOD;
			mul[u]=1;
		}
		if (add[u]!=0)
		{
			(val[C[u][0]]+=add[u])%=MOD;
			(sum[C[u][0]]+=1ll*add[u]*cnt[C[u][0]]%MOD)%=MOD;
			(add[C[u][0]]+=add[u])%=MOD;
			(val[C[u][1]]+=add[u])%=MOD;
			(sum[C[u][1]]+=1ll*add[u]*cnt[C[u][1]]%MOD)%=MOD;
			(add[C[u][1]]+=add[u])%=MOD;
			add[u]=0;
		}
		return ;
	}
	void Pushup(int u)
	{
		if (!u)
			return ;
		sum[u]=val[u]+sum[C[u][0]]+sum[C[u][1]];
		cnt[u]=1+cnt[C[u][0]]+cnt[C[u][1]];
		return ;
	}
	void Push(int u)
	{
		if (!isroot(u))
			Push(fa[u]);
		Down(u);
	}
	void Rotate(int u)
	{
		int v = fa[u], w = fa[v], t = Child(u);
		if (!isroot(v))
			C[w][Child(v)] = u;
		fa[C[u][t^1]] = v, C[v][t] = C[u][t^1];
		C[u][t^1] = v, fa[u] = w, fa[v] = u;
		Pushup(v);
		return ;
	}
	void Splay(int u)
	{
		Push(u);
		int v;
		while (!isroot(u))
		{
			v=fa[u];
			if(!isroot(v))
				Rotate((Child(u)==Child(v))?v:u);
			Rotate(u);
		}
		Pushup(u);
		return ;
	}
	void Access(int u)
	{
		int t=0;
		while (u)
		{
			Splay(u);
			C[u][1]=t;
			t=u;u=fa[u];
		}
		return ;
	}
	void Makeroot(int u)
	{
		Access(u);
		Splay(u);
		rev[u]^=1;
	}
	void Link(int u,int v)
	{
		Makeroot(u);
		fa[u]=v;
	}
	int Find(int u)
	{
		Access(u);Splay(u);
		while (C[u][0])
			u=C[u][0];
		return u;
	}
	inline void GetChain(int u,int v) {Makeroot(u),Access(v),Splay(v);}
	void Cut(int u,int v)
	{
		GetChain(u,v);
		C[v][0]=fa[u]=0;
	}
	void Add(int u,int v,int w)
	{
		GetChain(u,v);
		(add[v]+=w)%=MOD;
		(sum[v]+=1ll*cnt[v]*w)%=MOD;
		(val[v]+=w)%=MOD;
		return ;
	}
	void Mul(int u,int v,int w)
	{
		GetChain(u,v);
		Down(v);
		sum[v]=1ll*sum[v]*w%MOD;
		mul[v]=1ll*mul[v]*w%MOD;
		val[v]=1ll*val[v]*w%MOD;
		return ;
	}
	int CalcSum(int u,int v)
	{
		GetChain(u,v);
		return sum[v];
	}
};

inline bool IsOperator(char c){return (c=='+' || c=='/' || c=='*' || c=='-');}

inline int read()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

LinkCutTree LCT;
int n,q;
char opt;

int main()
{
//	freopen("P1501.in","r",stdin);
//	freopen("P1501.out","w",stdout);
	int x,y;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++)
		LCT.Add(i,i,1);
	for (int i=1;i<n;i++)
		LCT.Link(read(),read());
	for (int i=0;i<q;i++)
	{
		do {opt=getchar();}
			while (!IsOperator(opt));
		x=read(),y=read();
		if (opt=='+')
			LCT.Add(x,y,read());
		else if (opt=='-')
			LCT.Cut(x,y),LCT.Link(read(),read());
		else if (opt=='*')
			LCT.Mul(x,y,read());
		else
			printf("%d\n",LCT.CalcSum(x,y));
	}
	return 0;
}
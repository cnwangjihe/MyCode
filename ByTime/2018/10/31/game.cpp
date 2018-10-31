#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5009,
		  MAXM = 400009;

struct TMax
{
	long long v;
	int i;
	TMax (long long a=0,int b=0):v(a),i(b){}
	friend bool operator<(const TMax& a,const TMax& b) {return a.v<b.v;}
};

struct Tedge {int a,b;long long v;};

struct TLCT
{
	stack <int> Rec;
	int C[MAXM][2];
	TMax Max[MAXM];
	TMax Val[MAXM];
	int fa[MAXM],Rev[MAXM];
	int fp;
	TLCT() {fp=1;}
	void Free(int u) {Rev[u]=C[u][0]=C[u][1]=fa[u]=0,Val[u]=Max[u]=TMax();Rec.push(u);}
	int New(long long v=0)
	{
		int u;
		if (Rec.empty())
			u=fp++;
		else
			u=Rec.top(),Rec.pop();
		Val[u]=Max[u]=TMax(v,u);
		return u;
	}
	inline bool isroot(int u) {return C[fa[u]][0]!=u && C[fa[u]][1]!=u;}
	inline bool Child(int u) {return C[fa[u]][1]==u;}
	inline void Up(int u)
	{
		Max[u]=max(Val[u],max(Max[C[u][0]],Max[C[u][1]]));
		return ;
	}
	inline void Down(int u)
	{
		if (!Rev[u])
			return ;
		Rev[C[u][0]]^=1;
		Rev[C[u][1]]^=1;
		swap(C[u][0],C[u][1]);
		Rev[u]=0;
		return ;
	}
	void Push(int u)
	{
		if (!isroot(u))
			Push(fa[u]);
		Down(u);
		return ;
	}
	void Rotate(int u)
	{
		int v = fa[u], w = fa[v], t = Child(u);
		if (!isroot(v))
			C[w][Child(v)] = u;
		fa[C[u][t^1]] = v, C[v][t] = C[u][t^1];
		C[u][t^1] = v, fa[u] = w, fa[v] = u;
		Up(v);
		return ;
	}
	void Splay(int u)
	{
		int v;
		Push(u);
		while (!isroot(u))
		{
			v=fa[u];
			if (!isroot(v))
			{
				if (Child(u)==Child(v))
					Rotate(v);
				else
					Rotate(u);
			}
			Rotate(u);
		}
		Up(u);
		return ;
	}
	void Access(int u)
	{
		int t=0;
		while (u)
		{
			Splay(u);
			C[u][1]=t;
			Up(u);
			t=u;
			u=fa[u];
		}
		return ;
	}
	void Makeroot(int u)
	{
		Access(u);
		Splay(u);
		Rev[u]^=1;
		return ;
	}
	TMax Find(int x,int y)
	{
		Makeroot(x);
		Access(y);
		Splay(y);
		return Max[y];
	}
	void Cut(int x,int y)
	{
		int u=Find(x,y).i;
		Splay(u);
		fa[C[u][0]]=fa[C[u][1]]=0;
		Free(u);
		return ;
	}
	void Add(int x,int y,long long z)
	{
		int u=New(z);
		Makeroot(x);
		Makeroot(y);
		fa[x]=fa[y]=u;
		return ;
	}

};

TLCT LCT;
Tedge e[MAXM];
int fa[MAXN];
int n,m,k,q;
long long ans;

bool _cmp(Tedge a,Tedge b) {return a.v<b.v;}

inline long long readll()
{
	char ch=0;
	int w=0;
	long long x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}
inline int readint()
{
	char ch=0;
	int w=0,x=0;
	while(!isdigit(ch)) w|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return w?-x:x;
}

int _find(int u)
{
	int x=u,t;
	while (u!=fa[u])
		u=fa[u];
	while (x!=fa[x])
	{
		t=fa[x];
		fa[x]=u;
		x=t;
	}
	return u;
}

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int fx,fy,a,b;
	long long v;
	char opt;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
		LCT.New(),fa[i]=i;
	for (int i=0;i<m;i++)
		e[i].a=readint(),e[i].b=readint(),e[i].v=readll();
	sort(e,e+m,_cmp);
	for (int i=0;i<m;i++)
	{
		fx=_find(e[i].a),fy=_find(e[i].b);
		if (fx==fy)
			continue;
	//	cerr << e[i].a << ' ' << e[i].b << '\n';
		fa[fx]=fy;
		LCT.Add(e[i].a,e[i].b,e[i].v);
	}
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		do {opt=getchar();}
			while (opt!='g' && opt!='a');
		if (opt=='a')
		{
			a=readint(),b=readint(),v=readll();
			if (LCT.Find(a,b).v>v)
			{
				LCT.Cut(a,b);
				LCT.Add(a,b,v);
			}
		}
		else
		{
			long long t;
			ans=0;
			for (int j=0;j<k;j++)
			{
				t=LCT.Find(readint(),readint()).v;
				ans^=t;
			//	cerr << t << endl;
			}
			printf("%s\n",ans?"TimeCome":"TimeGone");
		}
	}
	return 0;
}
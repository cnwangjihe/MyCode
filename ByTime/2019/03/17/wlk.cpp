// Date      : 2019-03-17 19:36:04
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MOD  = 998244353,
		  MAXL = 55,
		  MAXC = 209,
		  MAXN = 22,
		  MAXM = MAXN*MAXN*26;

int _head[MAXN],_node[MAXM],_next[MAXM],_val[MAXM];
int a[MAXL],b[MAXL];
int f[MAXL][MAXC];
int nxt[MAXL],fail[MAXL][27];
int out[MAXN];
int alen,blen,cnt,n,m,fp=0;

inline int Add(int a,int b=0)
{
	int v=a+b;
	if (v>=MOD)
		v-=MOD;
	if (v<0)
		v+=MOD;
	return v;
}
inline int Mul(int a,int b) {return 1ll*a*b%MOD;}

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=1ll*a*a%MOD)
		if (k&(1<<i))
			ans=1ll*ans*a%MOD;
	return ans;
}

struct Gauss
{
	int a[MAXC][MAXC];
	void Clear(){memset(a,0,sizeof a);}
	inline void Set(int i,int j,int v) {a[i][j]=v;}
	inline int& At(int i,int j) {return a[i][j];}
	bool Solve(int n)
	{
		int inv,t;
		for (int i=0;i<n;i++)
		{
			for (int j=i;j<n;j++)
				if (a[j][i])
					for (int k=0;k<=n;k++)
						swap(a[i][k],a[j][k]);
			inv=Add(-qpow(a[i][i],MOD-2));
			for (int j=0;j<n;j++)
			{
				if (i==j || !a[j][i])
					continue;
				t=Mul(a[j][i],inv);
				for (int k=i;k<=n;k++)
					a[j][k]=Add(a[j][k],Mul(t,a[i][k]));
			}
		}
		for (int i=0;i<n;i++)
			a[i][n]=Mul(a[i][n],qpow(a[i][i],MOD-2));
		return 1;
	}
	void Copy(int *f,int n)
	{
		for (int i=0;i<n;i++)
			f[i]=a[i][n];
		return ;
	}
	void Output(int n)
	{
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<=n;j++)
				cerr << a[i][j] << ' ';
			cerr << '\n';
		}
		return ;
	}
};
Gauss G;

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

inline bool IsLetter(int v) {return v>=0 && v<26;}
void KMP(int *a,int len)
{
	nxt[0]=nxt[1]=0;
	int k=0;
	for (int i=1;i<len;i++)
	{
		while (k && a[i]!=a[k]) 
			k=nxt[k];
		if (a[i]==a[k])
			k++;
		nxt[i+1]=k;
	}
	for (int j=0;j<26;j++)
		fail[0][j]=0;
	fail[0][a[0]]=1;
	for (int i=1;i<len;i++) 
	{
		for (int j=0;j<26;j++)
			fail[i][j]=fail[nxt[i]][j];
		fail[i][a[i]]=i+1;
	}
	return ;
}

inline int GetId(int i,int j){return (i-1)*alen+j;}

int main()
{
//	freopen("wlk.in","r",stdin);
//	freopen("wlk.out","w",stdout);
//	freopen("debug.bug","w",stderr);
	memset(_head,-1,sizeof _head);
	int x,y;
	char s[10];
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%s",&x,&y,s);
		_connect(x,y,s[0]-'a');
		out[x]++;
	}
	memset(a,-1,sizeof a);
	memset(b,-1,sizeof b);
	do {a[0]=getchar()-'a';}
		while (!IsLetter(a[0]));
	do {a[++alen]=getchar()-'a';}
		while (IsLetter(a[alen]));
	a[alen]=-1;
//	cerr << "f**k\n";
	do {b[0]=getchar()-'a';}
		while (!IsLetter(b[0]));
	do {b[++blen]=getchar()-'a';}
		while (IsLetter(b[blen]));
	b[blen]=-1;
//	cerr << "f**k\n";
	KMP(a,alen);
	int cnt=GetId(n,alen);
//	cerr << cnt << '\n';
	for (int i=0;i<=cnt;i++)
		f[blen][i]=0;
	int v,uid,vid,p2;
	for (int k=blen-1;k>=0;k--)
	{
		G.Clear();
		for (int u=1;u<=n;u++)
		{
			int inv=qpow(out[u],MOD-2);
			for (int p1=0;p1<alen;p1++)
			{
				uid=GetId(u,p1);
				G.Set(uid,cnt,1);
				G.Set(uid,uid,1);
				for (int i=_head[u];~i;i=_next[i])
				{
					v=_node[i];
					p2=fail[p1][_val[i]];
					vid=GetId(v,p2);
					if (b[k]==_val[i])
						G.Set(uid,cnt,Add(G.At(uid,cnt),Mul(inv,(p2==alen)?0:f[k+1][vid])));
					else if (p2!=alen)
						G.Set(uid,vid,Add(G.At(uid,vid),-inv));
				}
			}
		}
	//	G.Output(cnt);
		G.Solve(cnt);
	//	G.Output(cnt);
		G.Copy(f[k],cnt);
	//	for (int i=0;i<cnt;i++)
	//		cerr << f[k][i] << ' ';
	}
	printf("%d\n",f[0][0]);
	return 0;
}
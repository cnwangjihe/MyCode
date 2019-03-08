#include<bits/stdc++.h>

using namespace std;


#define ls ch[p][0]
#define rs ch[p][1]
const int N = 1e5 + 10, inf = 1e9;
using std::max;
typedef long long LL;
typedef std::multiset<LL> MI;

MI Chain[N], Path[N];
int a[N], ch[N][2], fa[N], pr[N], to[N << 1], nx[N << 1], tp;
LL sum[N], lmx[N], rmx[N], mxs[N], Ans;
void add(int u, int v) {to[++tp] = v; nx[tp] = pr[u]; pr[u] = tp;}
void adds(int u, int v) {add(u, v); add(v, u);}
bool wh(int p) {return ch[fa[p]][1] == p;}
bool Ir(int p) {return ch[fa[p]][0] != p && ch[fa[p]][1] != p;}
void Era(MI &s, int v) {
	if(s.find(v) == s.end()) puts("ERRR");
	s.erase(s.find(v));
}
void Era(int u, int v) {
	Era(Chain[u], lmx[v]); Era(Path[u], mxs[v]);
}
void Ins(int u, int v) {
	Chain[u].insert(lmx[v]); Path[u].insert(mxs[v]); 
}
LL fir(MI &s) {return s.size() ? *s.rbegin() : -inf;}
LL sec(MI &s) {return s.size() > 1 ? *(++s.rbegin()) : -inf;}
void Re(LL &a, LL b) {a = max(a, b);}
void Up(int p) {
	sum[p] = sum[ls] + sum[rs] + a[p];
	LL cha = max(0LL, fir(Chain[p]));
	LL L = max(cha, rmx[ls]) + a[p];
	LL R = max(cha, lmx[rs]) + a[p];
	lmx[p] = max(lmx[ls], sum[ls] + R);
	rmx[p] = max(rmx[rs], sum[rs] + L);
	mxs[p] = max(rmx[ls] + R, lmx[rs] + L);
	Re(mxs[p], max(mxs[ls], mxs[rs]));
	Re(mxs[p], fir(Path[p]));
	Re(mxs[p], cha + sec(Chain[p]) + a[p]);
	Re(mxs[p], cha + a[p]);
}
void Rotate(int p) {
	int f = fa[p], g = fa[f], c = wh(p);
	if(!Ir(f)) ch[g][wh(f)] = p; fa[p] = g;
	ch[f][c] = ch[p][c ^ 1]; if(ch[f][c]) fa[ch[f][c]] = f;
	ch[p][c ^ 1] = f; fa[f] = p; Up(f);
}
void Splay(int p) {
	for(;!Ir(p); Rotate(p))
		if(!Ir(fa[p])) Rotate(wh(fa[p]) == wh(p) ? fa[p] : p);
	Up(p);
}
void Access(int u) {
	for(int p = u, pr = 0; p; pr = p, p = fa[p]) {
			cerr << p << ' ' << lmx[pr] << ' ' << rs << endl;
		Splay(p);
		if(pr) Era(p, pr);
		if(rs) Ins(p, rs);
		rs = pr; 
		Up(p);		
	}
	Splay(u);
}
void Change(int u, int v) {Access(u); a[u] = v; Up(u); Ans = mxs[u];}
LL Query(int p) {
	Access(p); LL res = 0;
	LL cha = max(0LL, fir(Chain[p]));
	LL L = max(cha, rmx[ls]) + a[p];
	LL R = max(cha, lmx[rs]) + a[p];
	res = max(rmx[ls] + R, lmx[rs] + L);
	Re(res, cha + sec(Chain[p]) + a[p]);
	Re(res, cha + a[p]);
	return res;
}
void Dfs(int u) {
	for(int i = pr[u]; i; i = nx[i])
		if(to[i] != fa[u]) {
			fa[to[i]] = u;
			Dfs(to[i]);
			Ins(u, to[i]);
		}
	Up(u);
}
int main() {
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int tn=n,x,y;
	for(int i = 2;i <= tn; ++i)
	{
		n++;
		scanf("%d",&x);
		adds(x, n);
		adds(n, i);
	}
	for(int i = 1;i <= n; ++i)
		a[i] = 0;
	for(int i = 0;i <= n; ++i)
		lmx[i] = rmx[i] = mxs[i] = -inf;
	Dfs(1); Ans = mxs[1];
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		Change(x+tn-1,y);
		printf("%lld\n", Ans);
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
#include<ctype.h>
#include<string.h>
#include<math.h>

using namespace std;
#define ll long long

inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	return (s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),(s==t?-1:*s++):*s++);
}
template<class T>
inline void read(T &x) {
	static bool iosig;
	static char c;
	for (iosig=false, c=read(); !isdigit(c); c=read()) {
		if (c == '-') iosig=true;
		if (c == -1) return;
	}
	for (x=0; isdigit(c); c=read()) x=((x+(x<<2))<<1)+(c^'0');
	if (iosig) x=-x;
}
const int OUT_LEN = 10000000;
char obuf[OUT_LEN], *ooh=obuf;
inline void print(char c) {
	if (ooh==obuf+OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh=obuf;
	*ooh++=c;
}
template<class T>
inline void print(T x) {
	static int buf[30], cnt;
	if (x==0) print('0');
	else {
		if (x<0) print('-'), x=-x;
		for (cnt=0; x; x/=10) buf[++cnt]=x%10+48;
		while(cnt) print((char)buf[cnt--]);
	}
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }

const int N = 1000005;
int n, m, num, root, lastans, top[N], son[N], s[N], b[N], a[N], w[N], siz[N], fa[N], h[N], e[N<<1], pre[N<<1], ch[N][2], f[N][2], g[N][2];
struct matrix{
	int a[2][2];
	inline matrix(){ memset(a, 0, sizeof a);}
	inline matrix(int x, int y){ a[0][0]=a[0][1]=x, a[1][0]=y, a[1][1]=-1e9;}
	inline matrix operator *(const matrix &rhs)const{
		matrix ans;
		for(int i=0; i<2; ++i) for(int j=0; j<2; ++j)
			ans.a[i][j]=max(a[i][0]+rhs.a[0][j], a[i][1]+rhs.a[1][j]);
		return ans;
	}
}F[N], G[N];

inline void add(int x, int y){ e[++num]=y, pre[num]=h[x], h[x]=num;}
void update(int x){ F[x]=F[ch[x][0]]*G[x]*F[ch[x][1]];}
int build(int l, int r){
	if(l>r) return 0;
	int x=(s[l-1]+s[r]+1)/2, L=l, R=r, t=r;
	while(L<=R){
		int mid=L+R>>1;
		if(s[mid]>=x) t=mid, R=mid-1; else L=mid+1;
	}
	int u=b[t];
	fa[ch[u][0]=build(l, t-1)]=u, fa[ch[u][1]=build(t+1, r)]=u;
	return update(u), u;
}
void dfs1(int u){
	siz[u]=1, f[u][1]=a[u];
	for(int i=h[u]; i; i=pre[i]) if(e[i]!=fa[u]){
		fa[e[i]]=u, dfs1(e[i]), siz[u]+=siz[e[i]];
		if(siz[e[i]]>siz[son[u]]) son[u]=e[i];
		f[u][0]+=max(f[e[i]][0], f[e[i]][1]), f[u][1]+=f[e[i]][0];
	}
	w[u]=siz[u]-siz[son[u]];
}
void dfs2(int u){
	if(son[u]) top[son[u]]=top[u], dfs2(son[u]);
	g[u][1]+=a[u];
	for(int i=h[u]; i; i=pre[i]) if(e[i]!=fa[u] && e[i]!=son[u]){
		top[e[i]]=e[i], dfs2(e[i]);
		g[u][0]+=max(f[e[i]][0], f[e[i]][1]), g[u][1]+=f[e[i]][0];
	}
	G[u]=matrix(g[u][0], g[u][1]);

	if(top[u]==u){
		int cnt=0;
		for(int j=u; j; j=son[j]) b[++cnt]=j, s[cnt]=s[cnt-1]+w[j];
		int tmp=fa[u];
		fa[root=build(1, cnt)]=tmp;
	}
}
int main() {
	read(n), read(m);
	for(int i=1; i<=n; ++i) read(a[i]);
	for(int i=1; i<n; ++i){
		static int x, y;
		read(x), read(y), add(x, y), add(y, x);
	}
	F[0].a[0][1]=F[0].a[1][0]=-1e9;
	dfs1(1), top[1]=1, dfs2(1);

	while(m--){
		static int x, y, v;
		read(x), read(y);
		x^=lastans;
		g[x][1]+=y-a[x], a[x]=y;
		G[x]=matrix(g[x][0], g[x][1]);
		while(x){
			v=fa[x];
			if(ch[v][0]!=x && ch[v][1]!=x)
				g[v][0]-=max(F[x].a[0][0], F[x].a[1][0]), g[v][1]-=F[x].a[0][0];
			update(x);
			if(ch[v][0]!=x && ch[v][1]!=x)
				g[v][0]+=max(F[x].a[0][0], F[x].a[1][0]), g[v][1]+=F[x].a[0][0],
				G[v]=matrix(g[v][0], g[v][1]);
			x=v;
		}
		print(lastans=max(F[root].a[0][0], F[root].a[1][0])), print('\n');
	}
	return flush(), 0;
}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

#define ll long long
#define uint unsigned

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define SZ(x) ((int)(x).size())
#define pb push_back

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(y < x) x = y;}

template<class T>
inline void read(T &x) {
	char c;int f = 1;x = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-') f = -1;else x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
	x *= f;
}

const int N = 2e3;
const int M = 4e6;

int n, m;
bool c[N + 9][N + 9];

struct graph {
	int sz, head[N + 9], to[M + 9], ne[M + 9];
	void init() {
		sz = 1, memset(head, 0, sizeof head);
	}
	void addedge(int u, int v) {
		to[sz] = v, ne[sz] = head[u], head[u] = sz++;
		to[sz] = u, ne[sz] = head[v], head[v] = sz++;
	}
}g;

#define L(x) (((x) << 1) - 1)
#define R(x) ((x) << 1)

int bel[N + 9], tot;

void dfs(int x) {
	bel[x] = tot;
	for(int i = g.head[x], y; i; i = g.ne[i])
		if(!bel[y = g.to[i]])
			dfs(y);
}

int main() {
//	freopen("2622.in", "r", stdin);
//	freopen("2622.out", "w", stdout);
	
	int T;
	read(T);
	while(T--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				c[i][j] = false;
		for(int i = 1; i <= m; ++i) {
			int u, v;
			read(u), read(v);
			c[u][v] = c[v][u] = true;
		}
		g.init();
		for(int i = 1; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j)
				if(!c[i][j]) {
					g.addedge(L(i), R(j));
					g.addedge(R(i), L(j));
				}
		std::fill(bel + 1, bel + n * 2 + 1, 0), tot = 0;
		for(int i = 1; i <= n * 2; ++i)
			if(!bel[i]) ++tot, dfs(i);
		bool flag = true;
		for(int i = 1; i <= n; ++i)
			if(bel[L(i)] == bel[R(i)]) {
				flag = false;
				break;
			}
			cerr << tot << endl;
		if(flag) puts("YES");
		else puts("NO");
	}

	fclose(stdin);fclose(stdout);
	return 0;
}

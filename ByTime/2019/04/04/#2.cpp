#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7 + 10;
const int Mod = 1e9 + 7;
int N, k;
char S[MAXN];
int now[MAXN]; char s[MAXN];
int rt[MAXN], ch[MAXN][4], fa[MAXN], len[MAXN], lst, cnt, f[MAXN];
int ans;

inline int id(char ch) {
	return ch == 'A' ? 0 : ch == 'C' ? 1 : ch == 'G' ? 2 : 3;
}

inline char iid(int c) {
	return c == 0 ? 'A' : c == 1 ? 'C' : c == 2 ? 'G' : 'T';
}

inline void extend(int i, int x) {
	int p, q, np, nq;
	p = lst; lst = np = ++cnt;
	len[np] = len[p] + 1;
	for(; p && !ch[p][x]; p = fa[p]) ch[p][x] = np;
	if(!p)
		fa[np] = rt[i];
	else {
		q = ch[p][x];
		if(len[q] == len[p] + 1)
			fa[np] = q;
		else{
			nq = ++cnt; len[nq] = len[p] + 1;
			memcpy(ch[nq], ch[q], sizeof(ch[q]));
			fa[nq] = fa[q];
			fa[q] = fa[np] = nq;
			for(; ch[p][x] == q; p = fa[p])
				ch[p][x] = nq;
		}
	}
}

inline void Dfs(int tp, int x) {
	puts(s + 1); ++ans;
	for(; now[tp] < 4; ++now[tp]) if(ch[x][now[tp]]) {
		s[tp + 1] = iid(now[tp]);
		now[tp + 1] = 0;
		Dfs(tp + 1, ch[x][now[tp]]);
		s[tp + 1] = 0;
	}
}

inline void Dp(int tp, int x) {
	if(f[x] > 0) return;
	f[x] = 1;
	for(; now[tp] < 4; ++now[tp]) if(ch[x][now[tp]]) {
		Dp(tp + 1, ch[x][now[tp]]);
		now[tp + 1] = 0;
		f[x] = (f[x] + f[ch[x][now[tp]]]) % Mod;
	}
}

int main() {
	freopen("copy.in", "r", stdin);
	freopen("copy2.out", "w", stdout);
	register int i, j, c;
	scanf("%d", &N); getchar();
	for(i = 1; i <= N; ++i) {
		gets(S + 1);
		lst = rt[i] = ++cnt; int l = strlen(S + 1);
		for(j = 1; j <= l; ++j)
			extend(i, id(S[j]));
	}
	for(i = N - 1; i; --i) for(j = rt[i]; j != rt[i + 1]; ++j) for(c = 0; c < 4; ++c) if(!ch[j][c])
		ch[j][c] = ch[rt[i + 1]][c];
	scanf("%d", &k);
	if(k) Dfs(0, rt[1]), printf("%d\n", ans);
	else Dp(0, rt[1]), printf("%d\n", f[rt[1]]);
	return 0;
}
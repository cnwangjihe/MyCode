#include <cstdio>
#include <bitset>
#include <iostream>
#include <set>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long
const int maxn = 5e4 + 7;
struct nt {
    int l, r, id, ts;
} ask[maxn];
struct nd {
    int x, pre, v;
} p[maxn];
int n, m, an[maxn], c[maxn], pos[maxn], num[maxn * 20], last[maxn], ans;
bool vis[maxn];
char s[9];
bool cmp(nt a, nt b) {
    return pos[a.l] < pos[b.l] ||
           pos[a.l] == pos[b.l] && pos[a.r] < pos[b.r] ||
           pos[a.l] == pos[b.l] && pos[a.r] == pos[b.r] && a.ts < b.ts;
}
void update(int x) {
    if(vis[x]) {
        if(!--num[c[x]]) --ans;
    }
    else if(++num[c[x]] == 1) ans++;
    vis[x] ^= 1;
}
void change(int x, int v) {
    if(vis[x]) {
        update(x); c[x] = v; update(x);
    }
    else c[x] = v;
}

int _sqrt(int n)
{
	int l=0,r=n+1,mid;
	while (l+1<r)
	{
		mid=(l+r)>>1;
		if ((long long)mid*mid<=(long long)n)
			l=mid;
		else
			r=mid;
	}
	return mid;
}

int main() {
    //("E:1.in", "r", stdin);
    scanf("%d%d", &n, &m);
    int x, y, tot = 0, top = 0;
    int bk = _sqrt(n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
        last[i] = c[i];
        pos[i] = i / bk;
    }
    for(int i = 1; i <= m; i++) {
        scanf("%s%d%d", s, &x, &y);
        x++;
        if(s[0] == 'Q') {
            ask[++tot].id = tot;
            ask[tot].l = x, ask[tot].r = y, ask[tot].ts = top;
        }
        else {
            p[++top].x = x, p[top].v = y, p[top].pre = last[x];
            last[x] = y;
        }
    }
    sort(ask + 1, ask + 1 + tot, cmp);
    int now = 0, pl = 1, pr = 0;
    for(int i = 1; i <= tot; i++) {
        if(now < ask[i].ts) {
            for(int j = now + 1; j <= ask[i].ts; j++)
                change(p[j].x, p[j].v);
        }
        else {
            for(int j = now; j >= ask[i].ts + 1; j--)
                change(p[j].x, p[j].pre);
        }
        if(pr < ask[i].r) {
            for(int j = pr + 1; j <= ask[i].r; j++)
                update(j);
        }
        else {
            for(int j = pr; j >= ask[i].r + 1; j--)
                update(j);
        }
        if(pl < ask[i].l) {
            for(int j = pl; j <= ask[i].l - 1; j++)
                update(j);
        }
        else {
            for(int j = pl - 1; j >= ask[i].l; j--)
                update(j);
        }
        pl = ask[i].l, pr = ask[i].r, now = ask[i].ts;
        an[ask[i].id] = ans;
    }
    for(int i = 1; i <= tot; i++) {
        printf("%d\n", an[i]);
    }
    return 0;
}

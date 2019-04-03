#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;
typedef long long ll;
template <class T>
void read(T &x){
    char c;
    bool op = 0;
    while(c = getchar(), c < '0' || c > '9')
    if(c == '-') op = 1;
    x = c - '0';
    while(c = getchar(), c >= '0' && c <= '9')
    x = x * 10 + c - '0';
    if(op) x = -x;
}
template <class T>
void write(T x){
    if(x < 0) putchar('-'), x = -x;
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 100005;
int n, m, a[N];
int ecnt, adj[N], nxt[2*N], go[2*N];
int fa[N], son[N], sze[N], top[N], idx[N], pos[N], tot, ed[N];
ll f[N][2];

struct matrix {
    ll g[2][2];
    matrix(){
    memset(g, 0, sizeof(g));
    }
    matrix operator * (const matrix &b) const {
    matrix c;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
        for(int k = 0; k < 2; k++)
            c.g[i][j] = max(c.g[i][j], g[i][k] + b.g[k][j]);
    return c;
    }
    void out()
    {
        for (int i=0;i<2;i++,cerr << '\n')
            for (int j=0;j<2;j++)
                cerr << g[i][j] << ' ';
        cerr << '\n';
    }
} val[N], data[4*N];

void add(int u, int v){
    go[++ecnt] = v;
    nxt[ecnt] = adj[u];
    adj[u] = ecnt;
}

void init(){
    static int que[N];
    que[1] = 1;
    for(int ql = 1, qr = 1; ql <= qr; ql++)
    for(int u = que[ql], e = adj[u], v; e; e = nxt[e])
        if((v = go[e]) != fa[u])
        fa[v] = u, que[++qr] = v;
    for(int qr = n, u; qr; qr--){
    sze[u = que[qr]]++;
    sze[fa[u]] += sze[u];
    if(sze[u] > sze[son[fa[u]]])
        son[fa[u]] = u;
    }
    for(int ql = 1, u; ql <= n; ql++)
    if(!top[u = que[ql]]){
        for(int v = u; v; v = son[v])
        top[v] = u, idx[pos[v] = ++tot] = v;
        ed[u] = tot;
    }
    for(int qr = n, u; qr; qr--){
    u = que[qr];
    f[u][1] = max(0, a[u]);
    for(int e = adj[u], v; e; e = nxt[e])
        if(v = go[e], v != fa[u]){
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
        }
    }
}

void build(int k, int l, int r){
    if(l == r){
    ll g0 = 0, g1 = a[idx[l]];
    for(int u = idx[l], e = adj[u], v; e; e = nxt[e])
        if((v = go[e]) != fa[u] && v != son[u])
        g0 += max(f[v][0], f[v][1]), g1 += f[v][0];
    data[k].g[0][0] = data[k].g[0][1] = g0;
    data[k].g[1][0] = g1;
    val[l] = data[k];
    return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    data[k] = data[k << 1] * data[k << 1 | 1];
}
void change(int k, int l, int r, int p){
    if(l == r){
    data[k] = val[l];
    return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) change(k << 1, l, mid, p);
    else change(k << 1 | 1, mid + 1, r, p);
    data[k] = data[k << 1] * data[k << 1 | 1];
}
matrix query(int k, int l, int r, int ql, int qr){
    if(ql <= l && qr >= r) return data[k];
    int mid = (l + r) >> 1;
    if(qr <= mid) return query(k << 1, l, mid, ql, qr);
    if(ql > mid) return query(k << 1 | 1, mid + 1, r, ql, qr);
    return query(k << 1, l, mid, ql, qr) * query(k << 1 | 1, mid + 1, r, ql, qr);
}
matrix ask(int u){
    return query(1, 1, n, pos[top[u]], ed[top[u]]);
}
void path_change(int u, int x){
    val[pos[u]].g[1][0] += x - a[u];
    a[u] = x;
    matrix od, nw;
    while(u){
    od = ask(top[u]);
    change(1, 1, n, pos[u]);
    nw = ask(top[u]);
    u = fa[top[u]];
    val[pos[u]].g[0][0] += max(nw.g[0][0], nw.g[1][0]) - max(od.g[0][0], od.g[1][0]);
    val[pos[u]].g[0][1] = val[pos[u]].g[0][0];
    val[pos[u]].g[1][0] += nw.g[0][0] - od.g[0][0];
    }
}

int main(){

    read(n);
    read(m);
    for(int i = 1; i <= n; i++) read(a[i]);
    for(int i = 1, u, v; i < n; i++)
    read(u), read(v), add(u, v), add(v, u);
    init();
    build(1, 1, n);
    int u, x;
    matrix t;
    for (int i=1;i<=n;i++)
        val[pos[i]].out();
    while(m--){
    read(u), read(x);
    path_change(u, x);
    t = ask(1);
    write(max(t.g[0][0], t.g[1][0])), enter;
    }

    return 0;
}
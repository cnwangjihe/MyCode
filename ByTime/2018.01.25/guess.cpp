#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
const int N = 105;
const int M = 5500;
int pre[N], nxt[M], to[M], ret[M], cost[M], cnt;
inline void _addEdge(int x, int y, int r, int c) {
  nxt[cnt] = pre[x];
  ret[cnt] = r;
  cost[cnt] = c;
  to[pre[x] = cnt++] = y;
}
void addEdge(int x, int y, int r, int c) {
  _addEdge(x, y, r, c);
  _addEdge(y, x, 0, -c);
}
int _que[N], dis[N], fa[N];
bool inque[N];
inline int& que(int x) { return _que[x % N]; }
bool SPFA(int S, int T) {
  int hd = 0, tl = 0;
  memset(dis, 0x7f, sizeof dis);
  memset(inque, 0, sizeof inque);
  bool ok = false;
  dis[S] = 0;
  inque[que(tl++) = S] = true;
  while (hd < tl) {
    int x = que(hd++);
    if (x == T) ok = true;
    for (int i = pre[x]; ~i; i = nxt[i])
      if (ret[i] && dis[to[i]] > dis[x] + cost[i]) {
        dis[to[i]] = dis[x] + cost[i];
        fa[to[i]] = i;
        if (!inque[to[i]])
          inque[que(tl++) = to[i]] = true;
      }
    inque[x] = false;
  }
  return ok;
}
int MCMF(int S, int T) {
  int ans = 0;
  while (SPFA(S, T)) {
    int minn = 0x7f7f7f7f;
    for (int i = T; i != S; i = to[fa[i] ^ 1])
      minn = std::min(minn, ret[fa[i]]);
    ans += minn * dis[T];
    for (int i = T; i != S; i = to[fa[i] ^ 1]) {
      ret[fa[i]] -= minn;
      ret[fa[i] ^ 1] += minn;
    }
  }
  return ans;
}
std::map<int, int> X, Y;
int cntX[N], cntY[N];
bool p[N][N];
int main() {
  freopen("guess.in", "r", stdin);
  freopen("guess.out", "w", stdout);
  int n;
  scanf("%d", &n);
  int x, y;
  int nx = 0, ny = 0;
  while (n--) {
    scanf("%d%d", &x, &y);
    if (X.count(x)) x = X[x];
    else x = X[x] = nx++;
    if (Y.count(y)) y = Y[y];
    else y = Y[y] = ny++;
    ++cntX[x]; ++cntY[y];
    p[x][y] = true;
  }
  int S = nx + ny, T = nx + ny + 1;
  memset(pre, -1, sizeof pre);
  for (int x = 0; x < nx; ++x)
    addEdge(S, x, cntX[x], 0);
  for (int y = 0; y < ny; ++y)
    addEdge(nx + y, T, cntY[y], 0);
  for (int x = 0; x < nx; ++x)
    for (int y = 0; y < ny; ++y)
      addEdge(x, nx + y, 1, p[x][y]);
  printf("%d\n", MCMF(S, T));
  return 0; 
}

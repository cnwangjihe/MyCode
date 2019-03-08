#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int Maxn = 0x3f3f3f3f;
const int L = 21, M = 1e6 + 5, N = 5e4 + 5;
const int dx[] = {-1, 1, 0, 0},
          dy[] = {0, 0, -1, 1};
int dis[N][L][L], h[N][2], G[L][L]; 
int lst[N], nxt[M], to[M], flw[M], cur[N], lev[N];
int n, m, T, E, R, l = 1, r = 1000, Ans = -1, src, des; 
bool vis[L][L]; char c[L][L];
template <class T> inline T Min(const T a, const T b) {return a < b? a : b;}
template <class T> inline void CkMax(T &a, const T b) {if (a < b) a = b;}
template <class T> inline void CkMin(T &a, const T b) {if (a > b) a = b;}
inline int get()
{
    char ch; bool f = false; int res = 0;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch == '-') f = true;
     else res = ch - '0';
    while ((ch = getchar()) >='0' && ch <= '9')
        res = (res << 3) + (res << 1) + ch - '0';
    return f? ~res + 1 : res;
}
inline void put(int x)
{
    if (x < 0)
      x = ~x + 1, putchar('-');
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
inline void add(const int x, const int y, const int z)
{
    nxt[++T] = lst[x]; lst[x] = T; to[T] = y; flw[T] = z;
    nxt[++T] = lst[y]; lst[y] = T; to[T] = x; flw[T] = 0;
}
inline bool Bfs()
{
    static int Qn, Q[N]; int x, y;
    for (int i = src; i <= des; ++i) cur[i] = lst[i], lev[i] = -1;
    Q[Qn = 1] = src; lev[src] = 0;
    for (int j = 1; j <= Qn; ++j)
    {
        x = Q[j];
        for (int i = lst[x]; i; i = nxt[i])
         if (flw[i] > 0 && lev[y = to[i]] == -1)
         {
             lev[y] = lev[x] + 1; Q[++Qn] = y;
             if (y == des) return true;
         }
    }
    return false;
}
inline int Dinic(const int x, const int fl)
{
    if (x == des) return fl;
    int Del, res = 0, y;
    for (int &i = cur[x]; i; i = nxt[i])
    if (flw[i] > 0 && lev[x] < lev[y = to[i]])
    {
        Del = Dinic(y, Min(flw[i], fl - res));
        if (Del)
        {
            flw[i] -= Del; flw[i ^ 1] += Del;
            res += Del; if (res == fl) break;
        }
    }    
    if (res != fl) lev[x] = -1;
    return res;
}
inline int MaxFlow()
{
    int res = 0;
    while (Bfs()) res += Dinic(src, Maxn);
    return res;
}
inline void Ready(const int s, const int px, const int py)
{
    memset(vis, false, sizeof(vis)); int x, y, t = 0, w = 1; 
    vis[px][py] = true; dis[s][px][py] = 0; h[w][0] = px; h[w][1] = py;
    while ((t++) < w)
     for (int i = 0; i < 4; ++i)
     {
        int tx = h[t][0] + dx[i], ty = h[t][1] + dy[i];
        if (tx < 1 || tx > n || ty < 1 || ty > m || vis[tx][ty] || c[tx - 1][ty - 1] != '.') continue;
        dis[s][tx][ty] = dis[s][h[t][0]][h[t][1]] + 1;
        h[++w][0] = tx; h[w][1] = ty; vis[tx][ty] = true;
     }
}
inline bool Judge(const int mi)
{
    src = 0; des = R + E * mi + 1; T = 1;
    memset(lst, 0, sizeof(lst));
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= m; ++j)
      if (c[i - 1][j - 1] == '.') add(src, G[i][j], 1);
    for (int k = 1; k <= E; ++k)
     for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
       if (c[i - 1][j - 1] == '.' && dis[k][i][j] <= mi) 
           add(G[i][j], (k - 1) * mi + R + dis[k][i][j], 1);
    for (int i = 1; i <= E; ++i)
     for (int j = 1; j <= mi; ++j) 
     {    
        int tmp = (i - 1) * mi + R; add(tmp + j, des, 1);
        if (j != mi) add(tmp + j, tmp + j + 1, Maxn);
     }
    return MaxFlow() == R;
}
int main()
{
    memset(dis, Maxn, sizeof(dis));
    n = get(); m = get(); 
    for (int i = 0; i < n; ++i) scanf("%s", c[i]);
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= m; ++j)
     if (c[i - 1][j - 1] == 'D') Ready(++E, i, j);
      else if (c[i - 1][j - 1] == '.') G[i][j] = ++R; 
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) Ans = mid, r = mid - 1;
         else l = mid + 1;
    } 
    if (Ans == -1) puts("impossible");
     else put(Ans);
    return 0;
}
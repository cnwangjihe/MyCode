#include <cstdio>
const int N = 100050;
int a[20][N];
bool vis[N];
int main() {
  freopen("kengdie.in", "r", stdin);
  freopen("kengdie1.out", "w", stdout);
  int n = 0, x, m, res;
  while ((res = scanf("%d", &x)) != EOF && !vis[x])
    vis[a[0][++n] = x] = true;
  if (res == EOF) return 0;
  for (int i = 0; i < 19; ++i)
    for (int j = 1; j <= n; ++j)
      a[i + 1][j] = a[i][a[i][j]];
  scanf("%d", &m);
  do {
    for (int k = 19; ~k; --k)
      if ((m >> k) & 1) x = a[k][x];
    printf("%d\n", x);
  } while (scanf("%d%d", &x, &m) != EOF);
  return 0;
} 

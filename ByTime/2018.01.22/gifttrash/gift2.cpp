#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 10005;
const int B = 1005;
void upd(int f[N], int a, int b, int c) {
  static int que[N], que2[N], hd, tl;
  if (!a)
    for (int i = 0; i < N; ++i)
      f[i] += b * c;
  else
    for (int t = 0; t < a; ++t) {
      hd = tl = 0;
      for (int i = 0; a * i + t < N; ++i) {
        int wi = f[i * a + t] - i * b;
        while (hd < tl && i - que[hd] > c) ++hd;
        while (hd < tl && que2[tl - 1] < wi) --tl;
        que[tl] = i; que2[tl++] = wi;
        f[i * a + t] = que2[hd] + i * b;
      }
    }
}
// g != t
void upd2(int f[N], const int g[N]) {
  for (int i = N - 1, j, l; ~i; --i) {
    int fi = f[i];
    for (j = 0, l = i; l + 3 < N; j += 4, l += 4) {
      f[l] = std::max(f[l], fi + g[j]);
      f[l + 1] = std::max(f[l + 1], fi + g[j + 1]);
      f[l + 2] = std::max(f[l + 2], fi + g[j + 2]);
      f[l + 3] = std::max(f[l + 3], fi + g[j + 3]);
    }
    for (; l < N; ++j, ++l)
      f[l] = std::max(f[l], fi + g[j]);
  }
}
int a[N], b[N], c[N], bl[N];
int f[N];
int blf[N / B + 5][N], ans[N][N];
int main() {
  freopen("gift.in", "r", stdin);
  freopen("gift2.out", "w", stdout);
  int n;
  scanf("%d", &n);
  bl[0] = -1;
  bl[n + 1] = 10000;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
    bl[i] = (i - 1) / B;
  }
  memset(f, 0, sizeof f);
  for (int i = 1; i <= n; ++i) {
    if (bl[i] != bl[i - 1]) memcpy(blf[bl[i]], f, sizeof f);
    upd(f, a[i], b[i], c[i]);
  }
  memset(f, 0, sizeof f);
  for (int i = n; i; --i) {
    if (bl[i] != bl[i + 1]) upd2(blf[bl[i]], f);
    upd(f, a[i], b[i], c[i]);
  }
  for (int k = 0; k <= (n - 1) / B; ++k) {
    int l = B * k + 1, r = std::min(n, B * (k + 1));
    for (int i = l; i <= r; ++i)
      memcpy(ans[i], blf[k], sizeof(blf[k]));
    for (int i = l; i <= r; ++i)
      for (int j = l; j <= r; ++j)
        if (i != j)
          upd(ans[i], a[j], b[j], c[j]); 
  }
  int q, d, e;
  scanf("%d", &q);
  while (q--) {
    scanf("%d%d", &d, &e);
    printf("%d\n", ans[d + 1][e]);
  }
  return 0;
}

#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1005;
void upd(int e, int f[N], int a, int b) {
  for (int i = e; i >= a; --i)
    f[i] = std::max(f[i], f[i - a] + b);
}
void upd(int e, int f[N], int a, int b, int c) {
  for (int k = 1; k <= c; k <<= 1) {
    upd(e, f, a * k, b * k);
    c -= k;
  }
  upd(e, f, a * c, b * c);
}
int a[N], b[N], c[N], f[N];
int main() {
  freopen("gift.in", "r", stdin);
  freopen("gift3.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
  int q, d, e;
  scanf("%d", &q);
  while (q--) {
    scanf("%d%d", &d, &e);
    for (int i = 0; i <= e; ++i) f[i] = 0;
    for (int i = 0; i < n; ++i) if (i != d)
      upd(e, f, a[i], b[i], c[i]);
    printf("%d\n", f[e]);
  }
  return 0;
}

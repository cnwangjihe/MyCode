#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 19 | 1; 
const int M = log2(N) + 3; 
const int mod = 998244353;

int n, m, t, cnt = -1, tp[M << 1][N];
int a[N], b[N], ans[N], Sa[N], Sb[N];
int rev[N], A[N], B[N], fac[N], ifac[N];

inline int inv(int x) { return 1ll * ifac[x] * fac[x - 1] % mod; }
inline int add(int x, int y) { return (x += y) < mod ? x : x - mod; }

inline int qpow(int _, int __) {
    int ___ = 1; 
    for (; __; _ = 1ll * _ * _ % mod, __ >>= 1) 
        if (__ & 1) ___ = 1ll * ___ * _ % mod;
    return ___;
}

inline void Math_Init(int n) {
    fac[0] = ifac[0] = 1; 
    for (int i = 1; i <= n; ++ i) 
        fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n] = qpow(fac[n], mod - 2);
    for (int i = n; i; -- i) 
        ifac[i - 1] = 1ll * ifac[i] * i % mod;
}

inline void NTT(int *a, int n, int fh) {
    for (int i = 0; i < n; ++ i) 
        if (i < rev[i]) swap(a[i], a[rev[i]]);;
    for (int Wn, limit = 2; limit <= n; limit <<= 1) {
        Wn = qpow(fh ^ 1 ? qpow(3, mod - 2) : 3, (mod - 1) / limit);
        for (int W = 1, j = 0; j < n; j += limit, W = 1) 
            for (int i = j; i < j + (limit >> 1); ++ i, W = 1ll * W * Wn % mod) {
                int a1 = a[i], a2 = 1ll * W * a[i + (limit >> 1)] % mod;
                a[i] = add(a1, a2), a[i + (limit >> 1)] = add(a1, mod - a2);
            }
    }
    if (fh ^ 1) for (int i = 0; i < n; ++ i) 
        a[i] = 1ll * a[i] * inv(n) % mod;
}

inline void Invpoly(int *a, int *b, int len) {
    int limit = 1, k = 0;
    if (len ^ 1) {
        Invpoly(a, b, len >> 1);
        while (limit < len * 2) limit <<= 1, ++ k;
        for (int i = 0; i < limit; ++ i) {
            A[i] = B[i] = 0;
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }
        for (int i = 0; i < len; ++ i) 
            A[i] = a[i], B[i] = b[i];
        NTT(A, limit, 1), NTT(B, limit, 1);
        for (int i = 0; i < limit; ++ i) 
            A[i] = 1ll * A[i] * B[i] % mod * B[i] % mod;
        NTT(A, limit, -1);
        for (int i = 0; i < len; ++ i) 
            b[i] = add(b[i], add(b[i], mod - A[i]));
    }   
    else b[0] = qpow(a[0], mod - 2);
}

inline void Derpoly(int *a, int len) {
    for (int i = 0; i < len - 1; ++ i) 
        a[i] = 1ll * (i + 1) * a[i + 1] % mod;
    a[len - 1] = 0;
}

inline void Solve(int l, int r, int *a, int *b) {
    if (l == r) return (void) (a[0] = 1, a[1] = mod - b[l]); 
    int mid = (l + r) >> 1, *a1 = tp[++ cnt], *a2 = tp[++ cnt], limit = 1, k = 0; 
    Solve(l, mid, a1, b), Solve(mid + 1, r, a2, b);
    while (limit <= r - l + 1) limit <<= 1, ++ k;
    for (int i = 0; i < limit; ++ i) 
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    NTT(a1, limit, 1), NTT(a2, limit, 1);
    for (int i = 0; i < limit; ++ i) 
        a[i] = 1ll * a1[i] * a2[i] % mod, a1[i] = a2[i] = 0;
    NTT(a, limit, -1), cnt -= 2;
}

inline void Get_S(int *a, int *f, int n) {
    int invf[N] = {0}, limit = 1, k = 0;
    while (limit < t * 2) limit <<= 1, ++ k;
    Solve(1, n, f, a);
    fill(f+t+1,f+limit,0);
    Invpoly(f, invf, limit >> 1);
    for (int i=0;i<=n;i++)
        cerr << invf[i] << ' ';
    cerr << '\n';
    Derpoly(f, limit);
    for (int i = 0; i < limit; ++ i) 
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    NTT(f, limit, 1), NTT(invf, limit, 1);
    for (int i = 0; i < limit; ++ i) 
        f[i] = 1ll * f[i] * invf[i] % mod;
    NTT(f, limit, -1);
    for (int i = limit - 2; ~i; -- i) 
        f[i + 1] = 1ll * f[i] * (mod - 1) % mod;
    f[0] = n;
    for (int i = 0; i < limit; ++ i) {
        if (i > t) f[i] = 0;
        f[i] = 1ll * f[i] * ifac[i] % mod;
    }
}

int main() {
    int limit = 1, k = 0;

    Math_Init(N - 5), scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++ i) scanf("%d", &b[i]);
    scanf("%d", &t), Get_S(a, Sa, n), Get_S(b, Sb, m); 
    for (int i=0;i<=n;i++)
        cerr << Sa[i] << ' ';
    cerr << '\n';

    while (limit <= t * 2) limit <<= 1, ++ k;
    for (int i = 0; i < limit; ++ i) 
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    NTT(Sa, limit, 1), NTT(Sb, limit, 1);
    for (int i = 0; i < limit; ++ i) 
        Sa[i] = 1ll * Sa[i] * Sb[i] % mod;
    NTT(Sa, limit, -1);

    for (int i = 1; i <= t; ++ i) 
        printf("%lld\n", 1ll * Sa[i] * fac[i] % mod * inv(n) % mod * inv(m) % mod);

    return 0;
}
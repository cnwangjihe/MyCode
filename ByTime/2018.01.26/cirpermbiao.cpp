#include <algorithm>
#include <cstdio>
#include <string.h>
const int N = 500005;
const int mod = 1000000007;
typedef long long LL;
LL D[N];
LL fac[N], inv[N], invfac[N];
int main()
{
	freopen("cirperm.cpp","w",stdout);
	for (int n=0;n<=100;n++)
	{
		memset(D,0,sizeof D);
		memset(fac,0,sizeof fac);
		memset(inv,0,sizeof inv);
		memset(invfac,0,sizeof invfac);
		D[0] = 1;
		D[0] = 1; D[1] = 0;
		for (int i = 2; i <= n; ++i) D[i] = (i - 1) * (D[i - 1] + D[i - 2]) % mod;
		inv[1] = 1;
		for (int i = 2; i <= n; ++i)
			inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		fac[0] = invfac[0] = 1;
		for (int i = 1; i <= n; ++i) {
			fac[i] = i * fac[i - 1] % mod;
			invfac[i] = inv[i] * invfac[i - 1] % mod;
		}
		LL ans = 0;
		for (int k = 2; k <= n; ++k) {
			LL ansk = 0, pk_ = 1;
			for (int t = 1; t * k <= n; ++t) {
				pk_ = pk_ * inv[k] % mod;
				LL l = fac[n] * invfac[n - t * k] % mod *
						pk_ % mod * invfac[t] % mod * D[n - k * t] % mod;
				//printf("%d\n", (int)l);
				ansk = (ansk + (t & 1 ? 1 : -1) * l) % mod;
			}
			//printf("%d\n", (ansk + mod) % mod);
			ans = (ans + ansk) % mod;
		}
		printf("if (n==%d) printf(\"\%d\\n\")\;else\n",n, ans);
	}
	return 0;
}

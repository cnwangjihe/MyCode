	
#include <cstdio>
#include <complex>
#include <cmath>
#include <algorithm>
#include <iostream>
using std::copy;
using std::fill;
 
const long long mod_v = 119 * (1 << 23) + 1;
const int MaxN = 10010;
long long a[MaxN], b[MaxN], c[MaxN];
long long eps[MaxN], inv_eps[MaxN];
int tot;
 
long long power(long long x, long long p)
{
	long long v = 1;
	while(p)
	{
		if(p & 1) v = x * v % mod_v;
		x = x * x % mod_v;
		p >>= 1;
	}
 
	return v;
}
 
void init_eps(int n)
{
	tot = n;
	long long base = power(3, (mod_v - 1) / n);
	long long inv_base = power(base, mod_v - 2);
	eps[0] = 1, inv_eps[0] = 1;
	for(int i = 1; i < n; ++i)
	{
		eps[i] = eps[i - 1] * base % mod_v;
		inv_eps[i] = inv_eps[i - 1] * inv_base % mod_v;
	}
}
 
long long inc(long long x, long long d) 
{
	x += d; 
	return x >= mod_v ? x - mod_v : x; 
}
 
long long dec(long long x, long long d) 
{
	x -= d; 
	return x < 0 ? x + mod_v : x; 
}
 
void transform(int n, long long *x, long long *w)
{
	for(int i = 0, j = 0; i != n; ++i)
	{
		if(i > j) std::swap(x[i], x[j]);
		for(int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
 
	for(int i = 2; i <= n; i <<= 1)
	{
		int m = i >> 1;
		for(int j = 0; j < n; j += i)
		{
			for(int k = 0; k != m; ++k)
			{
				long long z = x[j + m + k] * w[tot / i * k] % mod_v;
				x[j + m + k] = dec(x[j + k], z);
				x[j + k] = inc(x[j + k], z);
			}
		}
	}
}
 
void polynomial_inverse(int deg, long long* a, long long* b, long long* tmp)
{
	if(deg == 1)
	{
		b[0] = power(a[0], mod_v - 2);
		std::cerr << b[0] <<'\n';
	} else {
		polynomial_inverse((deg + 1) >> 1, a, b, tmp);
 
		int p = 1;
		while(p < deg << 1) p <<= 1;
		copy(a, a + deg, tmp);
		fill(tmp + deg, tmp + p, 0);
		transform(p, tmp, eps);
		transform(p, b, eps);
		for(int i = 0; i != p; ++i)
		{
			std::cerr << b[i] << ' ';
			b[i] = (2 - tmp[i] * b[i] % mod_v) * b[i] % mod_v;
			if(b[i] < 0) b[i] += mod_v;
		}
		std::cerr << '\n';
		transform(p, b, inv_eps);
		long long inv = power(p, mod_v - 2);
		for(int i = 0; i != p; ++i)
			b[i] = b[i] * inv % mod_v;
		fill(b + deg, b + p, 0);
 
	}
}
 
int main()
{
	init_eps(2048);
	int n;
	std::cin >> n;
	for(int i = 0; i != n; ++i)
		std::cin >> a[i];
	polynomial_inverse(n, a, b, c);
	std::cout << "inverse: ";
	for(int i = 0; i != n; ++i)
		printf("%lld ", (b[i] + mod_v) % mod_v);
	std::cout << std::endl;
	return 0;
}
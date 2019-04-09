#include <bits/stdc++.h>

using namespace std;

class IO
{
private:
	char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
	char wbuf[100000],*wp=wbuf;
	IO(){}
	struct ObjectCreator{ObjectCreator(){IO::GetInstance();}};
	static ObjectCreator _oc;
public:
	static IO &GetInstance(){static IO Instance;return Instance;}
	inline void flush() {fwrite(wbuf,1,wp-wbuf,stdout);wp=wbuf;}
	~IO(){flush();}
//	#ifndef DEBUG
		inline char getchar(){return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?-1:*rp1++;}
		inline void putchar(char c){(wp-wbuf==100000)?(flush()):void();*wp++=c;}
//	#endif
	inline void print(char c) {putchar(c);}
	inline void print(const char *s)
	{
		int n=strlen(s);
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline void print(const string s)
	{
		int n=s.size();
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline int scan(char *s,int (*check)(int c)=isgraph)
	{
		int n=0;short c=getchar();
		while (!check(c) && (~c))
			c=getchar();
		if (!~c)
			return 0;
		do {s[n++]=c,c=getchar();}
			while (check(c));
		s[n]='\0';
		return n;
	}
	inline int scan(string &s,int (*check)(int c)=isgraph)
	{
		int n=0;short c=getchar();
		s="";
		while (!check(c) && (~c))
			c=getchar();
		if (!~c)
			return 0;
		do {s+=c,c=getchar();n++;}
			while (check(c));
		return n;
	}
	template<typename Number> void print(Number x)
	{
		if (x<0)
			putchar('-'),x=-x;
		if (x>9)
			print(x/10);
		putchar(x%10+48);
	}
	template<typename Number> int scan(Number &x)
	{
		bool f=0;x=0;short c=getchar();
		while (!isdigit(c) && (~c))
			f|=(c=='-'),c=getchar();
		if (!~c)
			return 0;
		do {x=x*10+c-48,c=getchar();}
			while (isdigit(c));
		x=(f?x*-1:x);
		return 1;
	}
	inline void println(){putchar('\n');}
	#if __cplusplus >= 201103L
		template<typename Number,typename... Numbers>
		inline void print(Number x,Numbers... X) {print(x),print(X...);}
		template<typename Number,typename... Numbers>
		inline int scan(Number &x,Numbers &... X) {return scan(x)+scan(X...);}
	#else
		#warning Please use c++11 to enable all features of IO
	#endif
};

IO &IO=IO::GetInstance();

#define ll long long

const int e = 2005, mod = 1e9 + 7;
char s[e][4];
int f[e][e * 3][2], n, ans = 1, fac[e * 3], inv[e * 3], g[e * 3], cnt, a[e * 3], tot;

inline int ksm(int x, int y)
{
	int res = 1;
	while (y)
	{
		if (y & 1) res = (ll)res * x % mod;
		y >>= 1;
		x = (ll)x * x % mod;
	}
	return res;
}

inline void add(int &x, int y)
{
	x += y;
	if (x >= mod) x -= mod;
}

inline int c(int x, int y)
{
	if (x == y) return 1;
	if (x < y) return 0;
	return (ll)fac[x] * inv[x - y] % mod * inv[y] % mod;
}

inline int solve(int l, int r)
{
	int res = 0, i, sum = 0, j;
	f[l - 1][0][0] = 1;
	g[l - 1] = 0;
	for (i = l; i <= r; i++)
	if (s[i][1] == 'o' && s[i][3] == 'o')
	{
		sum = 0;
	//	puts("x");
		g[i] = g[i - 1] + 1; tot++;
		for (j = 1; j <= g[i]; j++) 
		{
			add(sum, f[i - 1][j - 1][0]);
			add(f[i][j][1], sum);
			add(f[i][j][0], sum);
		}
		sum = 0;
		for (j = g[i]; j >= 1; j--)
		{
			add(sum, f[i - 1][j][1]);
			add(f[i][j][1], sum);
			add(f[i][j][0], sum);
		} 
	//	for (j = 1; j <= g[i]; j++) 
	//	printf("i = %d j = %d %d %d\n", i, j, f[i][j][0], f[i][j][1]);
	//	for (j = 1; j <= g[i]; j++) f[i][j][0] = f[i][j][1];
	//	cout << f[i][1][0] << "," << f[i][2][0] << "," << f[i][3][0] << endl;
	}
	else if (s[i][1] == 'x' && s[i][3] == 'x')
	{
		g[i] = g[i - 1] + 3; tot += 3;
		sum = 0;
		for (j = 3; j <= g[i]; j++)
		{
			add(sum, f[i - 1][j - 3][0]);
			add(f[i][j][0], (ll)(j - 1) * (j - 2) % mod * sum % mod);
			add(f[i][j][1], (ll)(j - 1) * (j - 2) % mod * sum % mod);
		}
		sum = 0;
		for (j = g[i]; j >= 3; j--)
		{
			add(sum, f[i - 1][j - 2][1]);
			add(f[i][j][0], (ll)(j - 1) * (j - 2) % mod * sum % mod);
			add(f[i][j][1], (ll)(j - 1) * (j - 2) % mod * sum % mod);
		}
		sum = 0;
		for (j = 2; j <= g[i]; j++)
		{
			add(sum, f[i - 1][j - 2][0]);
			add(f[i][j][1], 2ll * (j - 1) * (g[i] - j) % mod * sum % mod);
		}
		sum = 0;
		for (j = 1; j < g[i]; j++)
		{
			add(sum, f[i - 1][j - 1][0]);
			add(f[i][j][1], (ll)(g[i] - j) * (g[i] - j - 1) % mod * sum % mod);
		}
	}
	else
	{
		g[i] = g[i - 1] + 2; tot += 2;
		sum = 0;
		for (j = 2; j <= g[i]; j++)
		{
			add(sum, f[i - 1][j - 2][0]);
			add(f[i][j][0], (ll)(j - 1) * sum % mod);
			add(f[i][j][1], (ll)(j - 1) * sum % mod);
		}
		//cout << f[5][2][1] << endl;
		sum = 0;
		for (j = g[i]; j >= 2; j--)
		{
			add(sum, f[i - 1][j - 1][1]);
			add(f[i][j][0], (ll)(j - 1) * sum % mod);
			add(f[i][j][1], (ll)(j - 1) * sum % mod);
		}
		//cout << f[5][2][1] << endl;
		sum = 0;
		for (j = 1; j <= g[i]; j++)
		{
			add(sum, f[i - 1][j - 1][0]);
			add(f[i][j][1], (ll)(g[i] - j) * sum % mod);
		//	cout << f[5][2][1] << "," << (g[i] - j) * sum << "," << g[i] - j
		//	<< " " << sum << endl;
		}
	//	for (j = 1; j <= g[i]; j++)
	//	printf("i = %d j = %d %d %d\n", i, j, f[i][j][0], f[i][j][1]);
	}
	a[++cnt] = g[r];
//	cout << "l = " << l << " r = " << r << " g = " << g[r] << endl;
	for (j = 1; j <= g[r]; j++) 
	{
		add(res, f[r][j][1]);
//		cout << "j = " << j << " f = " << f[r][j][0] << endl;
	}
//	cout << "res = " << res << endl; 
	return res;
}

inline void nie()
{
	puts("0");
	fclose(stdin);
	fclose(stdout);
	exit(0);
}

int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	int i, j;
	IO.scan(n);
	fac[0] = 1;
	for (i = 1; i <= 3 * n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	inv[3 * n] = ksm(fac[3 * n], mod - 2);
	for (i = 3 * n - 1; i >= 0; i--)
		inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
	for (j = 1; j <= 3; j++) 
		IO.scan(s[j]+1);
	if (s[n][1] == 'x' || s[n][3] == 'x' || s[1][1] == 'x' || s[1][3] == 'x') nie();
	for (i = 1; i < n; i++)
		if (s[i][1] == 'x' && s[i + 1][1] == 'x') nie();
		else if (s[i][3] == 'x' && s[i + 1][3] == 'x') nie(); 
	for (i = 1; i <= n; i = j + 1)
		if (s[i][2] == 'x')
		{
			j = i;
			while (j + 1 <= n && s[j + 1][2] == 'x') j++;
			ans = (ll)ans * solve(i, j) % mod;
		}
		else
		{
			j = i;
			if (s[i][1] == 'x') a[++cnt] = 1, ++tot;
			if (s[i][3] == 'x') a[++cnt] = 1, ++tot;
		}
//	cout << "tot =" << tot << endl;
	for (i = 1; i <= cnt; i++)
	{
		ans = (ll)ans * c(tot, a[i]) % mod;
	//	cout << tot << "," << a[i] << "," << c(tot, a[i]) << endl; 
		tot -= a[i];
	//	cout << "i = " << i << " a = " << a[i] << endl;
	}
	IO.print(ans);
	return 0;
}
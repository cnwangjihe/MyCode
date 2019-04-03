
class IO
{
private:
	char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
	char wbuf[100000],*wp=wbuf;
public:
	inline void flush() {fwrite(wbuf,1,wp-wbuf,stdout);wp=wbuf;}
	~IO(){flush();}
	#ifndef DEBUG
		inline char getchar(){return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?-1:*rp1++;}
		inline void putchar(char c){(wp-wbuf==100000)?(flush()):(void)0;*wp++=c;}
	#endif
	
	template<typename Number> void print(Number x)
	{
		_print(x);
		#ifdef DEBUG
			flush();
		#endif
	}
	inline void prints(const char *s)
	{
		int n=strlen(s);
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	inline void prints(const string s)
	{
		int n=s.size();
		for (int i=0;i<n;i++)
			putchar(s[i]);
		return ;
	}
	template<typename Number> void _print(Number x)
	{
		if (x<0)
			putchar('-'),x=-x;
		if (x>9)
			print(x/10);
		putchar(x%10+48);
	}
	template<typename Number> void scan(Number &x)
	{
		bool f=0;x=0;char c=getchar();
		while (!isdigit(c))
			f|=(c=='-'),c=getchar();
		do {x=x*10+c-48,c=getchar();}
			while (isdigit(c));
		x=(f?x*-1:x);
		return ;
	}
	inline void println(){putchar('\n');}
	#if __cplusplus >= 201103L
		template<typename Number,typename... Numbers>
		inline void print(Number x,Numbers... X) {print(x),putchar(' '),print(X...);}
		template<typename Number,typename... Numbers>
		inline void scan(Number &x,Numbers &... X) {scan(x),scan(X...);}
	#else
		#warning Please use c++11 to enable all features of IO
	#endif
}IO;
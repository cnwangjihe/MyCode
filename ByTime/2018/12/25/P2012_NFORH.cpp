// Date    : 2018-12-25 19:18:43
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf
// Notice  : 经过常数优化后的代码,如需更好理解,请转至P2012.cpp

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

#define MOD 1000000000

long long n,t1,t2,t3,t4,p1,p2;

inline void write(long long x)
{
    static char s[30];
    if(x==0)putchar('0');
    else 
    {
        int tot=0;
        for(;x;x/=10)s[++tot]=x%10+'0';
        while(tot)putchar(s[tot--]);
    }
    putchar(10);
}

int main()
{
//	freopen("P2012.in","r",stdin);
//	freopen("P2012.out","w",stdout);
	while (scanf("%lld",&n),n)
	{
		if (n<4)
		{
			printf("0\n");
			continue;
		}
		n-=4ll;
		p1=3ll,p2=2ll;
		t1=t2=1ll;
		t4=(n&1ll)?-1:1;
		while (n)
		{
			if (n&1ll)
				t1=t1*p1%MOD,t2=t2*p2%MOD;
			p1=p1*p1%MOD;
			p2=p2*p2%MOD;
			n>>=1ll;
		}
		t3=t2*t2%MOD;
		t4=t4*t3;
		t1=t1*t3%MOD;
		t2=t3*t2%MOD;
	//	std::cerr << t1 << ' ' << t2 << ' ' << t3 << ' ' << t4 << '\n';
		write(((81ll*t1-64ll*t2+6ll*t3+t4)%MOD+MOD)%MOD);
	}
	return 0;
}
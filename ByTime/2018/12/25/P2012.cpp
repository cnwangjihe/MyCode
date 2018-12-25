// Date      : 2018-12-25 19:18:43
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Notice    : TLE版本,但只是常数问题
// Algorithm : 指数型生成函数

#include <bits/stdc++.h>

//using namespace std; //not suggest anymore.Please use std::

const long long MOD = 1000000000;

long long n,t1,t2,t3,t4,t5;

inline long long read(){
	long long q=0;char ch=' ';
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')q=q*10ll+ch-'0',ch=getchar();
	return q;
}

long long qpow(long long a,long long k)
{
	long long ans=1;
	for (long long i=0;(1ll<<i)<=k;i++,a=a*a%MOD)
		if ((1ll<<i)&k)
			ans=ans*a%MOD;
	return ans;
}

int main()
{
	/*
	  e^x=x^0/0!+x^1/1!+x^2/2!+...+x^∞/∞!
	  e^ax[n]=(ax)^n/n!
	  (e^12x - 4*e^8x + 6*e^4x + e^-4x - 4)/256
	*/
//	freopen("P2012.in","r",stdin);
//	freopen("P2012.out","w",stdout);
	while (n=read())
	{
		if (n<4)
		{
			printf("0\n");
			continue;
		}
		t1=qpow(12,n-4)*81ll;
		t2=4ll*qpow(8,n-3)*2ll;
		t3=6ll*qpow(4,n-4);
		t4=qpow(-4,n-4);
		printf("%lld\n",((t1-t2+t3+t4)%MOD+MOD)%MOD);
	}
	return 0;
}
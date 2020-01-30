// Date      : 2019-04-23 09:51:46
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

struct Complex{int x,y,w;Complex(int t1=0,int t2=0,int t3=0):x(t1),y(t2),w(t3){}};

inline int Mod(const int &a){return a<0?a+MOD:a;}
inline int Add(const int &a,const int &b){return a+b>=MOD?a+b-MOD:a+b;}
inline int Mul(const int &a,const int &b){return 1ll*a*b%MOD;}

Complex Mul(const Complex &a,const Complex &b)
{return Complex(Add(Mul(a.x,b.x),Mul(a.w,Mul(a.y,b.y))),Add(Mul(a.x,b.y),Mul(a.y,b.x)),a.w);}

Complex qpow(Complex a,int k)
{
	Complex ans(1,0,a.w);
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if (k&(1<<i))
			ans=Mul(ans,a);
	return ans;
}

int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if ((1<<i)&k)
			ans=Mul(ans,a);
	return  ans;
}

int modsqrt(int a)
{
	int w,b;
	do {b=rand()%MOD;w=Add(Mul(b,b),Mod(-a));}
		while (qpow(w,(MOD-1)>>1)!=MOD-1);
	Complex ans=qpow(Complex(b,1,w),(MOD+1)>>1);
	return min(ans.x,Mod(-ans.x));
}


int main()
{
//	freopen("#1.in","r",stdin);
//	freopen("#1.out","w",stdout);
	int n;
	while (1)
	{
		scanf("%d",&n);
		int ans=modsqrt(n);
		printf("%d %d\n",ans,Mul(ans,ans));
	}
	return 0;
}
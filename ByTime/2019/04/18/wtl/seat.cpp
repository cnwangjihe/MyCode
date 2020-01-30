// Date      : 2019-04-18 11:36:30
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

int n,MOD;

inline int Mul(const int &a,const int &b){return 1ll*a*b%MOD;}
inline int Add(const int &a,const int &b){return a+b>=MOD?a+b-MOD:a+b;}
inline int Mod(const int &a){return a<0?a+MOD:a;}

inline int qpow(int a,int k)
{
	int ans=1;
	for (int i=0;(1<<i)<=k;i++,a=Mul(a,a))
		if ((1<<i)&k)
			ans=Mul(ans,a);
	return ans;
}

int main()
{
	freopen("seat.in","r",stdin);
	freopen("seat.out","w",stdout);
	scanf("%d%d",&n,&MOD);
	if (n==1)
		printf("1\n");
	else if (n==2)
		printf("%d %d\n%d %d\n",qpow(2,MOD-2),qpow(2,MOD-2),qpow(2,MOD-2),qpow(2,MOD-2));
	return 0;
}
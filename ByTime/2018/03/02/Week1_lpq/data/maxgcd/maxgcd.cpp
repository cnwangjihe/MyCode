#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define GET (ch>='0'&&ch<='9')
#define LL long long
#define MAXN 100010
using namespace std;
int T,n,top;
struct number
{
	int id;
	LL Gcd;
}sta[MAXN];
LL ans;
LL a[MAXN];
LL gcd(LL a,LL b)   {   return !b?a:gcd(b,a%b); }
inline void in(int &x)
{
	char ch=getchar();x=0;
	while (!GET)	ch=getchar();
	while (GET) x=x*10+ch-'0',ch=getchar();
}
inline void In(LL &x)
{
	char ch=getchar();x=0;
	while (!GET)	ch=getchar();
	while (GET) x=x*10+ch-'0',ch=getchar();
}
int main()
{
	in(T);
	while (T--)
	{
		in(n);ans=0;top=0;
		for (int i=1;i<=n;i++)
		{
			In(a[i]);sta[++top]=(number){i,0};
			int Top=0;
			for (int j=1;j<=top;j++)	sta[j].Gcd=gcd(sta[j].Gcd,a[i]);
			for (int j=1;j<=top;j++)
				if (j==1||sta[j].Gcd!=sta[j-1].Gcd) sta[++Top]=sta[j];
			top=Top;
			for (int j=1;j<=top;j++)	ans=max(ans,sta[j].Gcd*(i-sta[j].id+1));
		}
		printf("%lld\n",ans);
	}
}

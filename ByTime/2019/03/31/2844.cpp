// Date      : 2019-04-01 09:35:23
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : http://10.3.35.134/showproblem?id=2844
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const int MAXT = 2000009;

inline __int128 _read()
{
	__int128 a=0;
	char c=getchar();
	while (!isdigit(c))
		c=getchar();
	do {a=a*10+c-48;c=getchar();}
		while (isdigit(c));
	return a;
}

inline void _write(__int128 a)
{
	char c[1000];
	int fp=0;
	do {c[fp++]=a%10+48,a/=10;}
		while (a);
	while (fp--)
		putchar(c[fp]);
	return ;
}

inline __int128 _ceil(__int128 a,__int128 b) {return a<=0?0:(a/b+((a%b?1:0)));}

__int128 n,k,p,tar,ans;
__int128 t1,t2;

int main()
{
	freopen("2844.in","r",stdin);
	freopen("2844.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		n=_read(),k=_read(),p=_read(),tar=_read();
		ans=_ceil(tar,n*k);
		t1=_ceil(p,n*k);
		t2=n*k*t1-p;
		for (int i=1;i<=MAXT;i++)
		{
	//	cerr << (long long)ans << endl;
			if (n>k)
				k++;
			else
				n++;
			ans=min(ans,t1+_ceil(tar-t2,n*k));
			t1+=_ceil(p-t2,n*k);
			t2=n*k*_ceil(p-t2,n*k)-(p-t2);
		}
		_write(ans);
	}
	return 0;
}
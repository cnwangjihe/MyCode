#include <bits/stdc++.h>

using namespace std;

const int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

int _read()
{
	int a=0,c;
	do {c=getchar()-'0';}
		while (c<0 || c>9);
	do {a=a*10+c;c=getchar()-'0';}
		while (c>=0 && c<=9);
	return a;
}

int calcy(int y)
{
	if (y<0)
		return 0;
	return 365*y+y/4-y/100+y/400;
}

bool check(int a)
{
	for (int i=2;i*i<=a;i++)
		if (a%i==0)
			return 0;
	return 1;
}

int calc(int y,int m,int d)
{
	int ans=calcy(y-1);
	for (int i=1;i<m;i++)
		ans+=month[i];
	ans+=d;
	if ( ((y%100 && y%4==0) || y%400==0) && m>2 )
		ans++;
	return ans;
}

int main()
{
	freopen("r.in","r",stdin);
	freopen("r.out","w",stdout);
	int T,y,m,d,mo=calc(1926,8,17);
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		y=_read();m=_read();d=_read();
		if (!check(abs(calc(y,m,d)-mo)))
			puts("Haixing");
		else
			puts("Niubi");
	}
	return 0;
}
#include<bits/stdc++.h>

using namespace std ;

typedef long long ll;

const ll MAXN = 2005;

ll r,c,i,j,n,kop[4],si,sj;
char pri[MAXN][MAXN];

int main()
{
	freopen("frostrider.in","r",stdin);
	freopen("frostrider.out","w",stdout);
	

	scanf("%lld%lld%lld%lld%lld",&r,&c,&si,&sj,&n);
	kop[0]=(n-1)/4+(n>=1),kop[1]=(n-2)/4+(n>=2);
	
	kop[2]=(n-3)/4+(n>=3),kop[3]=(n-4)/4+(n>=4);
	for (ll i=0;i<4;i++) kop[i]=(i+1)*kop[i]+kop[i]*(kop[i]-1)*2;
	si=((si-kop[0]+kop[2]-1)%r+r)%r+1;
	sj=((sj-kop[3]+kop[1]-1)%c+c)%c+1;
	for (ll i=1;i<=r;i++)
		for (ll j=1;j<=c;j++)
			pri[i][j]='.';
	pri[si][sj]='@';
	ll top=(n-1)%4,ch=(n-1)%26;
	for (ll i=n;i>=max(n-max(r,c)*4,1ll);i--)
	{
		if (top==0||top==2)
		{
			ll op=(top==0)?1:-1;
			for (ll j=1;j<=min(r,i);j++)
			{
				ll ti=((si+op*j-1)%r+r)%r+1,tj=sj;
				if (pri[ti][tj]=='.') pri[ti][tj]=(char)(ch+65);
			}
			si=((si+op*i-1)%r+r)%r+1;
		}
		else
		{
			ll op=(top==3)?1:-1;
			for (ll j=1;j<=min(c,i);j++)
			{
				ll ti=si,tj=((sj+op*j-1)%c+c)%c+1;
				if (pri[ti][tj]=='.') pri[ti][tj]=(char)(ch+65);
			}
			sj=((sj+op*i-1)%c+c)%c+1;
		}
		top=(top+3)%4;
		ch=(ch+25)%26;
	}
	
	for (ll i=1;i<=r;i++,printf("\n"))
		for (ll j=1;j<=c;j++)
			printf("%c",pri[i][j]);

	return 0;
}
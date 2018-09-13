#include<bits/stdc++.h>

using namespace std ;

const long long MAXN = 2005;

long long r,c,i,j,n,kop[4],si,sj;
char pri[MAXN][MAXN];

int main()
{
//	freopen("frostrider.in","r",stdin);
//	freopen("frostrider.out","w",stdout);

	scanf("%lld%lld%lld%lld%lld",&r,&c,&si,&sj,&n);
	kop[0]=(n-1)/4+(n>=1),
	kop[1]=(n-2)/4+(n>=2);
	
	kop[2]=(n-3)/4+(n>=3),
	kop[3]=(n-4)/4+(n>=4);
	for (long long i=0;i<4;i++)
		kop[i]=(i+1)*kop[i]+kop[i]*(kop[i]-1)*2;
	si=((si-kop[0]+kop[2]-1)%r+r)%r+1;
	sj=((sj-kop[3]+kop[1]-1)%c+c)%c+1;

	for (long long i=1;i<=r;i++)
		for (long long j=1;j<=c;j++)
			pri[i][j]=0;
	pri[si][sj]='@';
	long long top=(n-1)%4,ch=(n-1)%26,times=max(n-max(r,c)*4,1ll);
	for (long long i=n;i>=times;i--)
	{
		if (top==0 || top==2)
		{
			long long op=(!top)?1:-1;
			for (long long j=1;j<=min(r,i);j++)
			{
				long long ti=((si+op*j-1)%r+r)%r+1,tj=sj;
				if (!pri[ti][tj])
					pri[ti][tj]=(ch+65);
			}
			si=((si+op*i-1)%r+r)%r+1;
		}
		else
		{
			long long op=(top==3)?1:-1;
			for (long long j=1;j<=min(c,i);j++)
			{
				long long ti=si,tj=((sj+op*j-1)%c+c)%c+1;
				if (!pri[ti][tj])
					pri[ti][tj]=(ch+65);
			}
			sj=((sj+op*i-1)%c+c)%c+1;
		}
		top=(top+3)%4;
		ch=(ch+25)%26;
	}
	for (long long i=1;i<=r;i++)
	{
		for (long long j=1;j<=c;j++)
			putchar(pri[i][j]==0?'.':pri[i][j]);
		putchar('\n');
	}
	return 0;
}
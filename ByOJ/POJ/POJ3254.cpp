#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int MAXSTATE = 1<<12;

int c=0,ans,n,m,fl;
int state[MAXSTATE];
int p[13][MAXSTATE];
int f[13];

void kick()
{
	for (int i=0;i<MAXSTATE;i++)
		if ( ( i & (i<<1) ) == 0 ) state[c++]=i;
}

int main()
{
	cin >> n >> m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			cin >> fl;
			f[i]+=fl<<(m-j);
		}
	
	kick();
	
	p[0][0]=1;
	
	for (int i=1;i<=n;i++)
	{
		for (int s=0;s<c;s++)
		{
			if ( (state[s] | f[i] )!=f[i] ) continue;
			for (int s1=0;s1<c;s1++)
			{
				if ( ((state[s1] | f[i-1] )==f[i-1]) && (state[s1] & state[s]) == 0 )
					p[i][s]=(p[i][s]+p[i-1][s1])%100000000;
			}
		}
	}
	
	for (int s=0;s<c;s++)
	{
		ans=(ans+p[n][s])%100000000;
	}
	cout << ans << endl;
	
}
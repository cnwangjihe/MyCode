#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int MAXSTATE = 1<<11;
int n,m;
long long p[13][MAXSTATE];

void dfs(int s,int s1,int i,int k)
{
	if (k>=m)
	{
		p[i][s]+=p[i-1][s1];
		return ;
	}
	if ( (s1&(1<<k))!=0 )
	{
		dfs(s,s1,i,k+1);
		if ( k!=0 &&  ( s & (1<<(k-1)) ) == 0 ) dfs( (s|(1<<k)|(1<<(k-1))) , s1 , i , k+1 );
	}
	else dfs( ( s | (1<<k) ) , s1 , i , k+1 );
}

int main()
{
	cin >> n >> m;
	while (n!=0 && m!=0)
	{
		memset(p,0,sizeof p);
		p[0][MAXSTATE-1]=1;
		dfs(0,MAXSTATE-1,1,0);
		for (int i=2;i<=n;i++)
		{
			for (int s1=0;s1<MAXSTATE;s1++)
			{
				if (p[i-1][s1]==0) continue;
				dfs(0,s1,i,0);
	//			cerr << p[i-1][s1];
			}
		}
		
		cout << p[n][(1<<m)-1] << endl;
		cin >> n >> m;
	}
}
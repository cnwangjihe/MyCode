#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int MAXSTATE = (1<<10);
int p[102][101][101];
int b[MAXSTATE];
int f[102];
int state[102];
int n,m,lastp,c;
char ch;

void kick()
{
	for (int s=0;s<(1<<m);s++)
		if ( ( s & (s<<1) ) == 0 && ( s & (s<<2) ) == 0 ) state[c++]=s;
}

void dfs(int s,int s1,int s2,int i,int k,int add)
{
	if (k>=m)
	{
		if (b[s]==-1) return ;
		p[i][b[s]][b[s1]] = max(p[i-1][b[s1]][b[s2]]+add,p[i][b[s]][b[s1]]);
		return ;
	}
	dfs(s,s1,s2,i,k+1,add);
	if ( ((( s1 & (1<<k) )==0 && ( s2 & (1<<k) )==0) || (i==1)) && ((( s & (1<<(k-1)) )==0  && ( s & (1<<(k-2)) )==0) || (k==0)) && ( f[i] & (1<<k) )==0 ) dfs(s|(1<<k),s1,s2,i,k+1,add+1);
	
}

int main()
{
	cin >> n >> m;
	for (int i=1;i<=n;i++)
		for (int j=0;j<m;j++)
		{
			cin >> ch;
			if (ch=='H') f[i]+=(1<<j);
		}
	
	kick();
	
	memset(p,-1,sizeof p);
	memset(b,-1,sizeof b);
	
	for (int i=0;i<c;i++) b[state[i]]=i;
	
	p[0][0][0]=0;
	lastp=0;
	dfs(0,0,0,1,0,0);
	
	for (int s1=0;s1<c;s1++) 
		if (p[1][s1][0]!=-1) dfs(0,state[s1],0,2,0,0);
	
	for (int i=3;i<=n;i++)
	{
		for (int s1=0;s1<c;s1++)
		{
			for (int s2=0;s2<c;s2++)
			{
			//	if ((state[s1]&state[s2])!=0) continue;
				if (p[i-1][s1][s2]==-1) continue;
				dfs(0,state[s1],state[s2],i,0,0);
			}
		}
	}
	int ans=0;
	for (int s1=0;s1<c;s1++)
		for (int s2=0;s2<c;s2++) ans=max(ans,p[n][s1][s2]);		
	cout << ans;
}
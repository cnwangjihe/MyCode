#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int oo = 1000000000;

int cost[100][100],v[100][100],q[100][100];
int f[5000002];
char s[100][100];
int n,m,t1,t2;

int main()
{
	freopen("1983.in","r",stdin);
	freopen("1983.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		t1=0;
		do
			{s[i][0]=getchar();}
		while (s[i][0]<'a' || s[i][0]>'z');
		do
			{s[i][++t1]=getchar();}
		while (s[i][t1]>='a' && s[i][t1]<='z');
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&cost[i][j]);
			
	for(int i=0;i<n;i++)
	{
		for(int pos=0;pos<m;pos++)
		{
			t1=0;
			for (int j=0;j<n;j++)
				if (s[i][pos]==s[j][pos])
				{
					t1=max(cost[j][pos],t1);
					v[i][pos]+=cost[j][pos];
					q[i][pos]|=(1<<j);
				}
			v[i][pos]-=t1;
		//	cerr << v[i][pos];
		}
	}
	
	for(int i=1;i<=((1<<n)-1);i++) f[i]=oo;
	f[0]=0;
	
	for(int i=0;i<((1<<n)-1);i++)
	{
	//	cerr << f[i] << ' ';
		for (int j=0;;j++)
			if( !(i&(1<<j)) )
			{
				t1=(1<<j);
				for(int pos=0;pos<m;pos++)
				{
					t2=q[j][pos];
					f[i|t1]=min(f[i|t1],f[i]+cost[j][pos]);
					f[i|t2]=min(f[i|t2],f[i]+v[j][pos]);
				}
				break; 
			}
	}
	printf("%d\n",f[((1<<n)-1)]);
	return 0;
}

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 100009;

int f[MAXN][3][2];
int p[3][2];
bool pd[MAXN];
int n,m,u,v,fp;
int _next[MAXN*2],head[MAXN],node[MAXN*2];

void connect(int a, int b)
{
	_next[fp]=head[a];
	node[fp]=b;
	head[a]=fp;
	fp++;
	return ;
}

void solve(int root)
{
//	cerr << "  x" << root << " ";
	pd[root]=1;
	for (int i=head[root];i!=-1;i=_next[i])
		if (!pd[node[i]])
		{
//			cerr << node[i] << "  ";
			solve(node[i]);
			int v=node[i];
			memcpy(p,f[root],sizeof p);
			for (int j=0;j<m+1;j++)
				for (int k=0;j+k<m+1;k++)
				{
//					if (root==5) cerr << "*";
					f[root][j+k][0]=max(f[root][j+k][0],p[j][0]+f[v][k][0]);
					f[root][j+k][1]=max(f[root][j+k][1],p[j][1]+f[v][k][0]);
					f[root][j+k][1]=max(f[root][j+k][1],p[j][0]+f[v][k][1]+1);
					if (j+k<m) 
						f[root][j+k+1][0]=max(f[root][j+k+1][0],p[j][1]+f[v][k][1]+1);
				}
		}
//	cerr << root << "x  ";
	return ;
}
/*
void _out()
{
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<3;j++)
			cerr << f[i][j][0] << ":" << f[i][j][1] << "  ";
		cerr << '\n';
	}
}*/

int main()
{
	memset(_next,-1,sizeof _next);
	memset(head,-1,sizeof head);
	memset(pd,0,sizeof pd);
	fp=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		connect(u,v);
		connect(v,u);
	}
	solve(1);
//	cerr << "ss";
//	cerr << f[0][1][0] << " " << f[1][1][0];
//	_out();
	printf("%d\n",n*2+m-2-max(f[1][1][0],f[1][m][0])); 
	return 0;
}
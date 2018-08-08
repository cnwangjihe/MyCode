#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 1009;

int f[MAXN][MAXN],gl[MAXN][MAXN],gr[MAXN][MAXN];
int sum[MAXN];
int ttt,n,v;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
	return x*f;
}
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

int main()
{
	int tmp;
	ttt=read();
	for (;ttt--;)
	{
		n=read();
		sum[0]=0;
		for (int i=1;i<=n;i++)
			v=read(),sum[i]=sum[i-1]+v,gl[i][i]=gr[i][i]=f[i][i]=v;
		for (int i=1;i<=n;i++)
			for (int j=1;j+i<=n;j++)
				tmp=i+j,
				f[j][tmp]=sum[tmp]-sum[j-1]-min(0,min(gl[j][tmp-1],gr[j+1][tmp])),
				gl[j][tmp]=min(gl[j][tmp-1],f[j][tmp]),
				gr[j][tmp]=min(gr[j+1][tmp],f[j][tmp]);
		write(f[1][n]);
		putchar('\n');
	}
	return 0;
}
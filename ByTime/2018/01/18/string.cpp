#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <set>

using namespace std;

const long long MOD = 1000000007ll;
const int INF = 2147483647,
		  MAXN= 12;

int n, m, k;
int g[MAXN],f[MAXN];
long long Stack[100000];
long long ans=0;
set<long long> _inStack;

/*
void _check(int v)
{
	while (v)
	{
		printf("%d",v%n);
		v/=n;
	}
	printf("\n");
	return ;
}
*/

void dfs(int x,int y,int z)
{
	if (x==n)
	{
		if (z==m)
			f[y]++;
		return ;
	}
	int tail;
	long long value;
	for (int i=1;i<=y+1;i++)
	{
		value=g[x]=i;
		tail=z;
		for (int j=x;j>=0;j--)
		{
	//		_check(value);
			if (!_inStack.count(value))
				_inStack.insert(value),
				Stack[tail++]=value;
			if (j) value=value*n+g[j-1];
	//		cerr << tail << '\n';
		}
		if (max(y,i)<=k && tail<=m)
			dfs(x+1,max(i,y),tail);
		for (int j=z;j<tail;j++)
			_inStack.erase(Stack[j]);
	//	cerr << "RETURN !";
	}
	return ;
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	if (m>n*(n+1)/2)
	{
		printf("0\n");
		return 0;
	}
	dfs(0,0,0);
	ans=f[0];
	long long c=1ll;
	for (int i=1;i<=min(k,n);i++)
	{
	//	cerr << f[i] << ' ' << c << endl;
		c=(((long long)(k-i+1+MOD)%MOD)*c)%MOD;
		ans+=(c*(long long)f[i])%MOD;
		ans%=MOD;
	}
	printf("%I64d\n",ans);
	return 0;
} 

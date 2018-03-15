#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

const int MAXN = 500009;
const long long MOD = 1000000007ll;

int n,k=0;
int cnt[MAXN];
long long f[MAXN];
//無根樹找重心變有根樹（可能要加點），然後hash判斷子樹相同情況
void work2()
{
	f[1]=2ll;
	f[2]=3ll;
	for (int i=3;i<=n;i++)
		f[i]=(f[i-2]*3ll)%MOD;
	printf("%I64d\n",f[n]);
	return ;
}

int main()
{
	freopen("request.in","r",stdin);
	freopen("request.out","w",stdout);
	int a,b;
	scanf("%d",&n);
	for (int i=0;i<n-1;i++)
	{
		scanf("%d%d",&a,&b);
		cnt[a]++,cnt[b]++;
	}
	bool flag=1;
	for (int i=1;i<=n;i++)
	{
		if (cnt[i]==1)
			k++;
		if (cnt[i]>2)
		{
			flag=0;
			break;
		}
	}
	if ((flag && k==2) || n==1)
	{
		work2();
		return 0;
	}
//	cerr << k << "df" << endl;
	return 0;
}
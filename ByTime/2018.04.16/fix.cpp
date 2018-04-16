#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

const int MAXN = 1000009,
		  MAXC = 1000009;
const long long MOD = 1000000007ll;

int a[MAXN],b[MAXN],ans[MAXN];
long long w[MAXN],vb[MAXN],v[MAXN];
int n,m,c,k=0;
bool flag,f[MAXN],vis[MAXN];
set<long long> bs;

void work0()
{
	int c[1009],ans[1009],k=0;
	bool flag=0;
	for (int i=1;i+m-1<=n;i++)
	{
		flag=1;
		memset(c,-1,sizeof c);
		for (int j=0;j<m;j++)
			if (~c[b[j+1]])
			{
				if (c[b[j+1]]!=a[i+j])
				{
					flag=0;
				//	cerr << i <<' ' << j << endl;
					break;
				}
			}
			else
				c[b[j+1]]=a[i+j];
		if (flag)
			ans[k++]=i;
	}
	printf("%d\n",k);
	for (int i=0;i<k;i++)
		printf("%d ",ans[i]);
	putchar('\n');
}

long long Pow(long long x,long long y)
{
	if (!y) return 1ll;
	long long temp=Pow(x,y>>1);
	temp=temp*temp%MOD;
	if (y&1LL) temp=temp*x%MOD;
	return temp;
}

int main()
{
	freopen("fix.in","r",stdin);
	freopen("fix.out","w",stdout);
	int ttt;
	scanf("%d%d",&ttt,&c);
	w[0]=1ll;
	for (int i=1;i<MAXN;i++)
		w[i]=(w[i-1]*2ll)%MOD;
	for (;ttt--;)
	{
		scanf("%d%d",&n,&m);
		k=0;
		memset(v,0,sizeof v);
		memset(vb,0,sizeof vb);
		memset(vis,0,sizeof vis);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=1;i<=m;i++)
			scanf("%d",&b[i]);
		if (n<m)
		{
			printf("0\n\n");
			continue;
		}
		if (n<=4000 && m<=4000)
		{
			work0();
			continue;
		}
		bs.clear();
		for (int i=1;i<=m;i++)
			vb[b[i]]+=w[i],vb[b[i]]%=MOD;
		for (int i=1;i<=c;i++)
			bs.insert(vb[i]);
		for (int i=1;i<=m;i++)
			v[a[i]]+=w[i],v[a[i]]%=MOD,vis[a[i]]=1;
		int cnt=0;
		for (int i=1;i<=c;i++)
		{
			if (!vis[i])
				continue;
			if (bs.find(v[i])!=bs.end())
				f[v[i]]=1,bs.erase(v[i]);
			else
				cnt++;//cerr << i << endl;
		}
		k=0;
		if (cnt==0)
			ans[k++]=1;
		long long sum=1,t,t2;
		for (int i=2;i+m-1<=n;i++)
		{
			t=Pow(sum*2%MOD,MOD-1);
			t2=Pow(sum,MOD-1);
			if (f[a[i-1]])
				bs.insert(v[a[i-1]]*t%MOD),f[a[i-1]]=0,cnt++;
			if (f[a[i+m-1]])
				bs.insert(v[a[i+m-1]]*t2%MOD),f[a[i+m-1]]=0,cnt++;
			v[a[i-1]]=(v[a[i-1]]-w[1]+MOD)%MOD;
			v[a[i+m-1]]=(v[a[i+m-1]]+w[m])%MOD;
			if (bs.find(v[a[i-1]]*t%MOD)!=bs.end())
				bs.erase(v[a[i-1]]),f[a[i-1]]=1,cnt--;
			if (bs.find(v[a[i+m-1]]*t2%MOD)!=bs.end())
				bs.erase(v[a[i+m-1]]),f[a[i+m-1]]=1,cnt--;
			if (cnt==0)
				ans[k++]=i;
			sum=sum*2%MOD;
			
		}
		printf("%d\n",k);
		for (int i=0;i<k;i++)
			printf("%d ",ans[i]);
		putchar('\n');
	}
	return 0;
}
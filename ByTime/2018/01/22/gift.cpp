#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1010,
		  MAX  = 1005;

struct Tgift {int a,b,c;};

int n,q,csum;
int q1[MAXN],q2[MAXN];
int ans[MAXN][MAXN],f[MAXN][MAXN];
int c[MAXN];
Tgift gift[MAXN];

void Update(int l,int r,int m)
{
	int tmp,a,b,c,head,tail;
	for (int i=0;i<MAX;i++)
		f[m][i]=f[m-1][i];
	for (int i=l;i<=r;i++)
	{
		a=gift[i].a,b=gift[i].b,c=gift[i].c;
		for (int j=0;j<a;j++)
		{
			head=1,tail=0;
			for (int k=0;k*a+j<MAX;k++)
			{
				tmp=f[m][k*a+j]-k*b;
				while (head<=tail && q1[tail]<tmp)
					tail--;
				tail++;
				q1[tail]=tmp;
				q2[tail]=k;
				while (head<=tail && k-q2[head]>c)
					head++;
				f[m][k*a+j]=q1[head]+k*b;
			}
		}
	}
}

void solve(int l,int r,int k)
{
	if (l==r)
	{
		for (int i=0;i<MAX;i++)
			ans[l][i]=f[k][i];
		return;
	}
	int mid=(l+r)/2;
	Update(mid+1,r,k+1);
	solve(l,mid,k+1);
	Update(l,mid,k+1);
	solve(mid+1,r,k+1);
	return ;
}

int main()
{
	freopen("gift.in","r",stdin);
	freopen("gift.out","w",stdout);
	int x,y;
	csum=0;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d%d%d",&gift[i].a,&gift[i].b,&gift[i].c);
	solve(0,n-1,0);
	for (int i=0;i<n;i++)
		c[i]=(gift[i].a!=0)?0:gift[i].b*gift[i].c,csum+=c[i];
	for (int i=0;i<n;i++)
		for (int j=0;j<MAX;j++)
			ans[i][j]+=csum-c[i];
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",ans[x][y]);
	}
	return 0;
}

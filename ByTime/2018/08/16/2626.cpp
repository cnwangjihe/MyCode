#include <bits/stdc++.h>

using namespace std;

const int MAX  = 100009,
		  INF  = 1000000009,
		  MAXN = 509;

int f[2][MAX*2];
int a[MAXN];
int n,sum=0;

int main()
{
	freopen("2626.in","r",stdin);
	freopen("2626.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int now=0,pre=1;
	for (int i=0;i<n;i++)
	{
		for (int j=-sum-a[i];j<=sum+a[i];j++)
			f[now][j+MAX]=-INF;
		for (int j=-sum;j<=sum;j++)
		{
			f[now][j+MAX]=max(f[now][j+MAX],f[pre][j+MAX]);
			f[now][j+MAX+a[i]]=max(f[now][j+MAX+a[i]],f[pre][j+MAX]+a[i]);
			f[now][j+MAX-a[i]]=max(f[now][j+MAX-a[i]],f[pre][j+MAX]+a[i]);
		}
		sum+=a[i];
		swap(now,pre);
	}
	printf("%d\n",f[pre][MAX]/2+(sum-f[pre][MAX]));
	return 0;
}
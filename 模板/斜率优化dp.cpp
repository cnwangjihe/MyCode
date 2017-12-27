#include<iostream>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<stdio.h>
#include<algorithm>

using namespace std;

const int MAXN = 200004,
		  MAXK=52;
const double oo = 200002.0*200002+200002;

int line[MAXN];
long long sum[MAXN];
double s1[MAXN],s2[MAXN],s3[MAXN];
double f[MAXN][2];
int a[MAXN];
int n,k,head,tail,now,last,pos;

bool _check(int j,int i)
{
	int x=line[head],y=line[head+1];
	double t1=f[y][j]+s3[y]-s1[y]-(f[x][j]+s3[x]-s1[x]),
		   t2=s2[i]*(sum[y]-sum[x]);
	if (t1-t2<0.0000001) return true;
	return false;
}

void _add(int x,int j)
{
	tail++;
	line[tail]=x;
	while (head+1<tail)
	{
		int p1=line[tail-1],p2=line[tail-2];
		double t1=((f[x][j]+s3[x]-s1[x])-(f[p1][j]+s3[p1]-s1[p1]))*(sum[p1]-sum[p2]),
			   t2=((f[p1][j]+s3[p1]-s1[p1])-(f[p2][j]+s3[p2]-s1[p2]))*(sum[x]-sum[p1]);
		if (t1-t2>0.0000001) break;
		tail--;
		line[tail]=line[tail+1];
	}
}


void _clean(int a)
{
	for (int i=0;i<=n;i++)
		f[i][a]=0;
	return ;
}

int main()
{
	freopen("2007.in","r",stdin);
	freopen("2007.out","w",stdout);
	
	scanf("%d%d",&n,&k);
	sum[0]=s1[0]=s2[0]=s3[0]=0;
	for (int i=1; i<=n; i++) 
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
		s1[i]=s1[i-1]+sum[i]*1.0/a[i];
		s2[i]=s2[i-1]+1.0/a[i];
		s3[i]=s2[i]*sum[i];
	}
	f[0][1]=0.0;
	for (int i=1; i<=n; i++) 
		f[i][1]=s1[i];
	now=0;last=1;
	for (int j=2; j<=k; j++)
	{
		head=1,tail=0;
		_clean(now);
		for (int i=j; i<=n; i++)
		{
			_add(i-1,last);
		//	cerr << _check(last,i) << endl;
			while (head<tail && _check(last,i)) head++;
			pos=line[head];
			f[i][now]=s3[pos]-s2[i]*sum[pos]-s1[pos]+f[pos][last]+s1[i];
		}
		swap(now,last);
	}
	printf("%.10f\n",f[n][last]);
	return 0;
}
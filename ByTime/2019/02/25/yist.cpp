// Date      : 2019-02-25 08:35:54
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const long double PI  = 3.14159265358979323846264338327950288,
				  eps = 1e-10;
const int MAXN = 9,
		  INF  = 1000000009;

int r[MAXN],a[MAXN],b[MAXN];
bool f[MAXN];
int n;

inline bool _cmp(int a,int b) {return a>b;}

long double Calc(int n)
{
	int lim=INF;
	a[n]=a[0];
	for (int i=0;i<n;i++)
		b[i]=a[i]*a[i+1],lim=min(lim,b[i]);
	long double l=-lim,r=lim,mid,sum;
	while (l+eps<r)
	{
		mid=(l+r)/2.0,sum=0;
		for (int i=0;i<n;i++)
			sum+=acos(mid/b[i]);
		if (sum>=2*PI)
			l=mid;
		else
			r=mid;
	}
	if (l+eps>lim || r-eps<-lim)
		return 0;
	sum=0;
	for (int i=0;i<n;i++)
		sum+=b[i]*sin(acos(l/b[i]));
	return sum/2.0;
}

long double Search(int k)
{
	long double ans=0;
	if (k>=3)
		ans=max(ans,Calc(k));
	for (int i=0;i<n;i++)
		if (!f[i])
		{
			f[i]=1,a[k]=r[i];
			ans=max(ans,Search(k+1));
			a[k]=0,f[i]=0;
		}
	return ans;
}


int main()
{
	freopen("yist.in","r",stdin);
	freopen("yist.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&r[i]);
	sort(r,r+n,_cmp);
	a[0]=r[0],f[0]=1;
	a[1]=r[1],f[1]=1;
	printf("%.10Lf\n",Search(2));
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200009,
		  MAXM = 20;
const long long MOD = 1000000007;

struct Tquery{int l,r,i;};

Tquery q[MAXN],t[MAXN];
int n,m,k;
int a[MAXN];
long long f[MAXN][MAXM];
long long ans[MAXN];

void solve(int l,int r,int al,int ar)
{
	if (l==r)
	{
		for (int i=al;i<=ar;i++)
			ans[q[i].i]=(a[l]==0?2:1);
		return ;
	}
	int mid=(l+r)/2;
	for (int i=0;i<m;i++)
		f[mid][i]=0,f[mid+1][i]=0;

	f[mid][a[mid]]=1,f[mid][0]++;
	for (int i=mid-1;i>=l;i--)
	{
		for (int j=0;j<m;j++)
			f[i][j]=(f[i+1][j]+f[i+1][(j+m-a[i])%m])%MOD;
	}

	f[mid+1][a[mid+1]]=1,f[mid+1][0]++;
	for (int i=mid+2;i<=r;i++)
		for (int j=0;j<m;j++)
			f[i][j]=(f[i-1][j]+f[i-1][(j+m-a[i])%m])%MOD;

/*	for (int i=l;i<=r;i++)
	{
		for (int j=0;j<m;j++)
			cerr << i << ' ' << j << ' ' << f[i][j] << '\n';
		cerr << '\n';
	}
*/
	int cl=al,cr=ar;
	long long sum;
	for (int i=al;i<=ar;i++)
	{
		if (q[i].l<=mid && q[i].r>mid)
		{
			sum=0;
			for (int j=0;j<m;j++)
				(sum+=f[q[i].l][j]*f[q[i].r][(m-j)%m]%MOD)%=MOD;
			ans[q[i].i]=sum;
		}
		else
		{
			if (q[i].r<=mid)
				t[cl++]=q[i];
			else
				t[cr--]=q[i];
		}
	}
	for (int i=al;i<cl;i++)
		q[i]=t[i];
	for (int i=ar;i>cr;i--)
		q[i]=t[i];
	solve(l,mid,al,cl-1);
	solve(mid+1,r,cr+1,ar);
	return ;
}

int main()
{
	freopen("2567.in","r",stdin);
	freopen("2567.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]%=m;
	}
	scanf("%d",&k);
	for (int i=1;i<=k;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].i=i;
	}
	solve(1,n,1,k);
	for (int i=1;i<=k;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
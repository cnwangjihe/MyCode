#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50009;
/*
struct Tnum{int v,p;};

Tnum a[MAXN];
int v[MAXN],p[MAXN];
int n;

bool _cmp(Tnum a,Tnum b) {return a.v<b.v;}

int main()
{
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].v);
		a[i].p=i;
	}
	sort(a+1,a+n+1,_cmp);
	for (int i=1;i<=n;i++)
	{
		p[i]=a[i].p;
		v[a[i].p]=i;
	}
	int l,r;
	for (int j=0;j<400;j++)
		for (int i=1;i<=n;i++)
		{
			if (p[i]==i)
				continue;
			l=i,r=p[i];
			if (l>r)
				swap(l,r);
			if (l+1==r || l+2==r)
			{
				printf("%d %d\n",l,r);
				p[v[i]]=p[i];
				swap(v[p[i]],v[i]);
				p[i]=i;
				continue;
			}
			if (r-l>30)
				continue;
			printf("%d %d\n",l+1,r);
			printf("%d %d\n",l,l+1);
			printf("%d %d\n",l+1,r);
			p[v[i]]=p[i];
			swap(v[p[i]],v[i]);
			p[i]=i;
		}
	for (int i=1;i<=n;i++)
	{
		if (p[i]==i)
			continue;
		l=i,r=p[i];
		if (l>r)
			swap(l,r);
		if (l+1==r || l+2==r)
		{
			printf("%d %d\n",l,r);
			p[v[i]]=p[i];
			swap(v[p[i]],v[i]);
			p[i]=i;
			continue;
		}
		printf("%d %d\n",l+1,r);
		printf("%d %d\n",l,l+1);
		printf("%d %d\n",l+1,r);
		p[v[i]]=p[i];
		swap(v[p[i]],v[i]);
		p[i]=i;
	}
	printf("-1 -1\n");
	return 0;
}*/

typedef long long ll;

int n,m,a[MAXN];
map<int,int> mp;
ll sum;

inline int read()
{
	int x=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar());
	for (;c>='0'&&c<='9';c=getchar())
		x=x*10+(c^48);
	return x;
}

void modify(int l,int r)
{
	printf("%d %d\n",l,r);
	sum+=r-l+1;
	reverse(a+l,a+r+1);
}

int c[MAXN],b[MAXN];

void solve(int l,int r,int al,int ar)
{
	if (r<=l || al==ar)
		return ;
	
	int L=l,R=r,mid=(al+ar)>>1,cnt;
	
	while (L<=R)
	{
		for (;a[L]<=mid;L++);
		for (;a[R]>mid;R--);
		
		c[0]=1;b[0]=L;cnt=1;
		for (int i=L+1;i<=R;i++)
		{
			if ((a[i]<=mid)!=(a[i-1]<=mid)) 
			{
				c[cnt]=1^c[cnt-1];
				b[cnt]=i;
				cnt++;
			}
		}
		b[cnt]=R+1;
		
		int mx=0,mxi=-1;
		for (int i=0;i<cnt;i++)
			if (mx<b[i+1]-b[i])
				mx=b[i+1]-b[i],mxi=i;
		if (!~mxi)
			break;
		if (c[mxi])
			modify(b[mxi],R);
		else
			modify(L,b[mxi+1]-1);
	}
	solve(l,R,al,mid);
	solve(L,r,mid+1,ar);
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read(),mp[a[i]]=0;
	m=0;
	for (map<int,int>::iterator it=mp.begin();it!=mp.end();it++)
		it->second=m++;
	for (int i=1;i<=n;i++)
		a[i]=mp[a[i]];
	solve(1,n,0,m-1);
	printf("-1 -1\n");
	return 0;
}
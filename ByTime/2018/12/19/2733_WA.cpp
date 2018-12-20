// Date    : 2018-12-19 19:29:20
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

const int MAXN = 51,
		  MAXK = 20;

int a[MAXN],lg[1<<(MAXK)],v[MAXK];
int status[1<<(MAXK)],minus[1<<(MAXK)];
long long ans;
int n,s,k,sum;

inline int count(int a)
{
	static int cnt;
	cnt=0;
	while (a)
	{
		cnt++;
		a^=a&-a;
	}
	return cnt;
}

long long search(int k,int s1,int s2)
{
	if (k==n)
		return (s1==s2);
	return search(k+1,s1&a[k],s2)+search(k+1,s1,s2&a[k]);
}

void force()
{
	for (int i=0;i<n;i++)
		a[i]-=sum;
	std::sort(a,a+n);
	printf("%lld\n",search(0,(1<<MAXK)-1,(1<<MAXK)-1));
	return ;
}

int main()
{
	freopen("2733.in","r",stdin);
	freopen("2733.out","w",stdout);
//	int tcounter=clock();
	int T;
	scanf("%d",&T);
	for (int i=0;i<MAXK;i++)
		lg[(1<<i)]=i;
	for (int cn=1;cn<=T;cn++)
	{
		ans=0;
		memset(v,0,sizeof v);
		scanf("%d",&n);
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			sum=(!i)?a[i]:sum&a[i];
		}
	//	if (n<=24)
	//	{
	//		force();
	//		continue;
	//	}
		for (int i=0;i<MAXK;i++)
		{
			if (sum&(1<<i))
				continue;
			for (int j=0;j<n;j++)
				if (a[j]&(1<<i))
					v[i]|=(1<<j);
		}
		status[0]=(1<<MAXK)-1;
		minus[0]=-1;
		for (int i=1;i<(1<<MAXK);i++)
		{
			minus[i]=minus[i^(i&-i)]*-1;
			status[i]=status[i^(i&-i)]&v[lg[i&-i]];
			ans+=minus[i]*((1<<count(status[i]))-1);
		}
		printf("%lld\n",((1ll<<(n-1))-ans-1)*2ll);
	}
//	std::cerr << "\ntime: " << clock()-tcounter <<'\n';
	return 0;
}
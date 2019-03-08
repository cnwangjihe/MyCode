#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>

typedef long double lf;
typedef long long ll;

const int N=55;

int n,t;

int run()
{
	static int v[N];
	for(int i=1;i<=n;i++)v[i]=0;

	int cnt=0,ret=0,x;
	while(cnt<n)
	{
		x=rand()%n+1,v[x]++;
		if(v[x]==t)cnt++;
		ret++;
	}
	return ret;
}

int main()
{
	srand(time(0));

rep:
	printf("please input n & t : ");

	scanf("%d%d",&n,&t);

	if(n<=0 || t<=0){printf("Nao Yu Guo Tai Qiang Le\n");goto rep;}

	ll cnt=1,tmp;
	lf ans=run();

	while(1)
	{
		tmp=run();
		ans=(ans*cnt+tmp)/(cnt+1);
		cnt++;

		if(cnt%1000==0)printf("average : %.20Lf  |  count : %lld\n",ans,cnt);
	}

	return 0;
}

#include <bits/stdc++.h>

using namespace std;

int ans1,ans2,sum;
int a,b;

int main()
{
	freopen("2678.in","r",stdin);
	freopen("2678.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		int tmp;
		ans1=ans2=sum=0;
		scanf("%d%d",&a,&b);
		for (int i=0;i<=30 && (1<<i)<=b;i++)
		{
			if (a&(1<<i))
			{
				ans1+=(1<<i);
				tmp=a-sum+(1<<i)-1;
				if (b<=tmp)
					ans2+=(1<<i);
			}
			else
			{
				tmp=a-sum+(1<<i);
				if (b>=tmp)
					ans1+=(1<<i);
			}
			sum+=a&(1<<i);
		}
		printf("Case %d: %d %d\n",cn,ans1,ans2);
	}
	return 0;
}
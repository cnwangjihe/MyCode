#include <bits/stdc++.h>

using namespace std;

int step(int v)
{
	int ans=1;
	while (v%10==0)
		ans*=10,v/=10;
	return ans;
}

int getlen(int v)
{
	int ans=0;
	while (v)
		v/=10,ans++;
	return ans;
}

int calc(int v)
{
	while (v%10==0)
		v/=10;
	return v%10==5?getlen(v)*2-1:getlen(v)*2;
}

int a,b,ans;

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&a,&b);
		ans=1147483647;
		for (int i=a;i<=b;i+=step(i))
			ans=calc(ans)>calc(i)?i:ans;
		printf("%d\n",ans);
	}
	return 0;
}
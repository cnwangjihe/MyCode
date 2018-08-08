#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int t,n,m,k;
int main()
{
	freopen("number.in","r",stdin);
	freopen("number2.out","w",stdout);
	cin>>t;
	for (int i=1;i<=t;i++)
	{
		scanf("%d %d %d",&n,&m,&k);
		if (n>k && m>k) printf("%d\n",k+1);
		if (n>k && m<=k)printf("%d\n",m);
		if (n<=k && m>k)printf("%d\n",n);
		if (n<=k && m<=k)printf("%d\n",max(0,n+m-k-1));
	}
	return 0;
} 

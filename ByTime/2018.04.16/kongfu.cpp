#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

long long a1,b1,a2,b2;

long long calc(long long x,long long y)
{
	if(x>y)
		swap(x,y);
	if(!x) return 0ll;
	if(x%4ll==2ll)
		return (y&1)?0:(x/4ll)*4ll+3ll;
	if(x%4ll==0ll)
		return (y&1)?0:(x/4ll)*4ll;
	if(x%4ll==3ll)
		return 0ll;
	if(x%4ll==1ll)
		return (y&1ll);
}

int main()
{ 
	freopen("kongfu.in","r",stdin);
	freopen("kongfu.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%lld%lld%lld%lld",&a1,&b1,&a2,&b2);
		printf("%lld\n",calc(a2,b2)^calc(a1-1ll,b2)^calc(a2,b1-1ll)^calc(a1-1ll,b1-1ll));
	}
	return 0;
} 

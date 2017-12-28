#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

const long long INF = 1000000000000000009ll;

long long f,t,t0,a1,t1,p1,a2,t2,p2,j;
long long tt,ff,ans=INF;

int main()
{
	freopen("2346.in","r",stdin);
	freopen("2346.out","w",stdout);
	scanf("%lld%lld%lld",&f,&t,&t0);
	scanf("%lld%lld%lld",&a1,&t1,&p1);
	scanf("%lld%lld%lld",&a2,&t2,&p2);

	if (t1>t2) swap(t1,t2),swap(a1,a2),swap(p1,p2);

	for (long long i=0;a1*i<f;i++)
	{
		ff=f-i*a1;
		tt=t-i*a1*t1;
		if (ff*t2>tt && ff*t0>tt) continue;
		if (t0<=t2 || ff*t0<=tt) j=0;
			else j=((t0*ff-tt+t0-t2-1)/(t0-t2)+a2-1)/a2;
		ans=min(ans,p1*i+p2*j);
	}
	if (f*t1<=t) ans=min(ans,(f+a1-1)/a1*p1);
	if (ans==INF) printf("-1\n");
		else printf("%lld\n",ans);
	return 0;
}

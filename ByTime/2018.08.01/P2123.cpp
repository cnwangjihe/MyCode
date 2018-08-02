#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20009;

struct Tman{int a,b,d;};

Tman v[MAXN];
long long ans,sum;
int n;

inline bool _cmp(Tman a,Tman b){return (a.d!=b.d)?(a.d<b.d):((a.d<=0)?(a.a<b.a):(a.b>b.b));}

int main()
{
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d",&n);
		for (int i=0;i<n;i++)
		{
			scanf("%d%d",&v[i].a,&v[i].b);
			v[i].d=(v[i].a-v[i].b<0)?-1:(v[i].a-v[i].b==0?0:1);
		}
		sort(v,v+n,_cmp);
		ans=v[0].a+v[0].b;
		sum=v[0].a;
		for (int i=1;i<n;i++)
			ans=max(ans,sum+=v[i].a)+v[i].b;
		printf("%lld\n",ans);
	}
	return 0;
}
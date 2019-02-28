// Date      : 2019-02-19 10:23:20
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const double eps = 1e-10,
			 INF = 1.0/0.0;
const int MAXN = 1009;

struct Troom {double x,y;double p;};

Troom a[MAXN],b[MAXN];
int used[MAXN],out[MAXN];
double ans=0;
int n,m;

inline double GetK(const Troom& a,const Troom& b) {return (a.y-b.y)/(a.x-b.x);}
inline bool cmp(const Troom& x,const Troom& y) {return x.x<y.x;}


int Calc(int cnt)
{
	if (cnt<=2)
		return 0;

	int p,pa,pb,st=0;
	double last,now,k;
	fill(out,out+n+1,0);

	for (int i=1;i<=m;i++)
		if (used[i] && (st==0 || b[i].x<b[st].x))
			st=i;

	p=st,last=INF;
	for (pa=1;pa<=n && a[pa].x<b[st].x;pa++);
	while (p)
	{
		now=-INF,pb=0;
		for (int i=1;i<=m;i++)
		{
			k=GetK(b[p],b[i]);
			if (used[i] && p!=i && k+eps<last && k-eps>now)
				now=k,pb=i;
		}
		for (;pa<=n && a[pa].x<b[pb].x;pa++)
			if (GetK(a[pa],b[p])-eps>GetK(a[pa],b[pb]))
				out[pa]=1;
		last=now,p=pb;
	}

	p=st,last=-INF;
	for (pa=1;pa<=n && a[pa].x<b[st].x;pa++);
	while (p)
	{
		now=INF,pb=0;
		for (int i=1;i<=m;i++)
		{
			k=GetK(b[p],b[i]);
			if (used[i] && p!=i && k+eps<now && k-eps>last)
				now=k,pb=i;
		}
		for (;pa<=n && a[pa].x<b[pb].x;pa++)
			if (!(GetK(a[pa],b[p])-eps>GetK(a[pa],b[pb])))
				out[pa]=1;
		last=now,p=pb;
	}
	int ans=0;
	for (int i=1;i<=n;i++)
		if (!out[i])
			ans++;
	return ans;
}

void Search(int k,double p,int cnt)
{
	if (k==m+1)
	{
		ans+=1.0*p*Calc(cnt);
		return ;
	}
	used[k]=1;
	Search(k+1,p*b[k].p,cnt+1);
	used[k]=0;
	Search(k+1,p*(1-b[k].p),cnt);
	return ;
}

void Force1()
{
	ans=0;
	std::sort(a,a+n,cmp);
	Search(1,1,0);
	printf("%0.9f\n",ans);
	return ;
}

int main()
{
	freopen("stage.in","r",stdin);
	freopen("stage.out","w",stdout);

	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].x,&a[i].y),a[i].p=0;
	for (int i=1;i<=m;i++)
		scanf("%lf%lf%lf",&b[i].x,&b[i].y,&b[i].p);
	Force1();
	return 0;
}

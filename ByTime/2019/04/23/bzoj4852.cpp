// Date      : 2019-04-23 19:38:58
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-2;

const int MAXN = 1009;

double ax[MAXN],ay[MAXN],bx[MAXN],by[MAXN],br[MAXN];
int n,m,r,ans;

inline double rd(){return 1.0*rand()/RAND_MAX;}

inline double GetDis(const double &x1,const double &y1,const double &x2,const double &y2)
{return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));}

int Calc(double x,double y)
{
	double cr=r;
	int ans=0;
	for (int i=0;i<n;i++)
		cr=min(cr,GetDis(x,y,bx[i],by[i])-br[i]);
	if (cr<eps)
		return 0;
	for (int i=0;i<m;i++)
		if (GetDis(x,y,ax[i],ay[i])<=cr)
			ans++;
	return ans;
}

void Fire(int x,int y,double T)
{
	double d=0.998;
	int last;
	ans=max(ans,last=Calc(x,y));
	while (T>eps)
	{
		double tmp=T+0.1;
		int nx=x+(2*tmp)*rd()-tmp,ny=y+(2*tmp)*rd()-tmp;
		int val=Calc(nx,ny),de=val-last;
		if (de<=0)
		{
			if (exp(1e4*de/T)>rd())
				x=nx,y=ny,last=val;
		}
		else
		{
			ans=max(ans,val);
			last=val;
			x=nx,y=ny;
		}
		T=T*d;
	}
}

int main()
{
	freopen("bzoj4852.in","r",stdin);
	freopen("bzoj4852.out","w",stdout);
	srand(19260817);
	double x,y;
	scanf("%d%d%d",&n,&m,&r);
	for (int i=0;i<n;i++)
		scanf("%lf%lf%lf",&bx[i],&by[i],&br[i]);
	for (int i=0;i<m;i++)
		scanf("%lf%lf",&ax[i],&ay[i]);
	ans=0;
	for (int i=0;i<=20;i++)
	{
		x=40000.0*rd()-20000,y=40000.0*rd()-20000;
		Fire(x,y,2000);
	}
	srand(190817);
	for (int i=0;i<=10;i++)
	{
		x=400.0*rd()-200,y=400.0*rd()-200;
		Fire(x,y,200);
	}
	printf("%d\n",ans);
	return 0;
}
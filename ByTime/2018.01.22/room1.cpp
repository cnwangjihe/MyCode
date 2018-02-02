#include<bits/stdc++.h>
using namespace std;

const double eps=1e-7;
const double INF=(double)1000000000.0;
const int KASHIXIAN=3e6;
const int N=105;

int n,T;
int node[N];
double dis[N];

double sqr(double x)
{
	return x*x;
}

struct Tnode
{
	double x,y;
	
	Tnode(){}
	Tnode(double xx,double yy){
		x=xx;y=yy;
	}
	
	Tnode operator - (const Tnode &A)const{
		return Tnode(x-A.x,y-A.y);
	}
	
	friend double sqr(Tnode A){
		return (double)A.x*A.x+(double)A.y*A.y;
	}
	
	friend double getdis(Tnode A,Tnode B){
		return sqr(A-B);
	}
	
	friend double cross(Tnode A,Tnode B){
		return 1.0*fabs(A.x*B.y-A.y*B.x)/2.0;
	}
	
	friend double getk(Tnode A,Tnode B){
		
	}
};
Tnode a[N],b[N],O;

int main()
{
	freopen("room.in","r",stdin);
	freopen("room1.out","w",stdout);
	
	scanf("%d%d%d",&n,&O.x,&O.y);
	double ans=1.0*INF;
	for(int i=1;i<=n;++i)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	
	if(n==0)
	{
		double area=cross(a[3]-a[1],a[2]-a[1]);
		for(int i=1;i<=n;++i)
		{
			double now=0.0;
			now+=sqrt(getdis(O,a[i]));
			now+=area/getdis(a[i%n+1],a[(i%n+1)%n+1]);
///			double k=getk(a[i%n+1],a[(i%n+1)%n+1]);
//			double b=getb(k,a[i%n+1]);
		}
		printf("%0.2f\n",ans);
	}
	else
	{
		T=KASHIXIAN/n;
		while(T--)
		{
//			printf("%d\n",T);
			double now=0.0;
			for(int i=1;i<=n;++i)
				node[i]=rand()%10000+1;
			for(int i=1;i<=n;++i)
			{
				int j=i==n?1:i+1;
				double ks=(double)(a[j].y-a[i].y)/(double)(a[j].x-a[i].x);
				double bs=(double)a[i].y-(double)a[i].x*ks;
				b[i].x=(double)node[i]*(a[j].x-a[i].x)/10000.0+a[i].x;
				b[i].y=(double)node[i]*(a[j].y-a[i].y)/10000.0+a[i].y;
			}
			now+=sqrt(sqr(b[1].x)+sqr(b[1].y));
			now+=sqrt(sqr(b[n].x)+sqr(b[n].y));
			for(int i=1;i<n;++i)
				now+=sqrt(sqr(b[i].x-b[i+1].x)+sqr(b[i].y-b[i+1].y));
			if(ans-now>eps)
				ans=now;
		}
		for (int i=1;i<=n;i++)
			dis[i]=sqrt(sqr(O.x-a[i].x)+sqr(O.y-a[i].y));
		ans=min(ans,2.0*min(dis[1]+dis[3],dis[2]+dis[4]));
		printf("%0.2f\n",ans);
	}
	
	return 0;
}

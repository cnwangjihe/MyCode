#include<bits/stdc++.h>
using namespace std;
#define eps 1e-8
#define N 3050

const long double pi=acos(-1.0);

struct Point
{
	long double x,y;
	Point(){}
	Point(long double _x,long double _y):x(_x),y(_y){}
}	p[N],newp[N],tempp[N];

Point operator-(Point a,Point b)
{
	return Point(a.x-b.x,a.y-b.y);
}

int id[N];
long double ans,val[N];

bool cmp(int a,int b)
{
	return val[a]<val[b];
}

int F(long double x)
{
    if  (x>eps) return 1;
    if  (x<-eps) return -1;
    return 0;
}

long double Cross(Point a,Point b)
{
    return a.x*b.y-a.y*b.x;
}

long double Dot(Point a,Point b)
{
    return a.x*b.x+a.y*b.y;
}

void Solve(Point p[],int n)
{
int i,last;
long double ans1,ans2,sumx,sumy,allx,ally;
	for (i=1;i<n;i++) p[i]=p[i]-p[0];
	for (i=0;i<=n-2;i++) p[i]=p[i+1];
	n--;
	for (i=0;i<n;i++) id[i]=i;
	for (i=0;i<n;i++) val[i]=atan2(p[i].y,p[i].x);
	sort(id,id+n,cmp);
	for (i=0;i<n;i++) tempp[i]=p[id[i]];
	for (i=0;i<n;i++) p[i]=tempp[i];
	for (i=n;i<n+n;i++) p[i]=p[i-n];
	last=-1;
	sumx=sumy=allx=ally=0;
	for (i=0;i<n;i++)
	{
		allx+=p[i].x;
		ally+=p[i].y;
	}
	for (i=0;i<n;i++)
	{
	    for (;last<i;last++)
	    {
			sumx+=p[last+1].x;
			sumy+=p[last+1].y;
	    }
		for (;last+1-i+1<=n&&
            (F(Cross(p[i],p[last+1]))>0||F(Cross(p[i],p[last+1]))==0&&
            F(Dot(p[i],p[last+1]))>0&&F(Cross(p[last],p[last+1]))==0);last++)
		{
			sumx+=p[last+1].x;
			sumy+=p[last+1].y;
		}
		ans1=p[i].x*(sumy-p[i].y)-p[i].y*(sumx-p[i].x);
		ans2=p[i].y*(allx-sumx)-p[i].x*(ally-sumy);
		ans+=(ans1+ans2);
		sumx-=p[i].x;
		sumy-=p[i].y;
	}
}

int main()
{
int cas,n,i;

//    freopen("2593.in", "r", stdin);
//    freopen("2593.out", "w", stdout);
	cin>>cas;
	while (cas--)
	{
	    cin>>n;
		for (i=0;i<n;i++)
        {
            cin>>p[i].x>>p[i].y;
            assert(p[i].x==round(p[i].x)&&p[i].y==round(p[i].y));
        }
		if  (n<=2)
		{
			cout<<"0.000000"<<endl;
			continue;
		}
		ans=0;
		for (i=0;i<n;i++)
		{
			swap(p[i],p[0]);
			memcpy(newp,p,sizeof(newp));
			Solve(newp,n);
		}
		cerr <<ans << endl;
		ans=ans*(n/3)/2/n/(n-1)/(n-2);
		cout<<fixed<<setprecision(6)<<ans<<endl;
	}
}
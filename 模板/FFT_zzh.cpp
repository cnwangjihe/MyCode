#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int mx=4e6+10;

int n,m;
struct complex
{
	double x,y;
	complex(double nx=0,double ny=0)
	{ x=nx,y=ny; }
	complex operator + (complex a)
	{ return complex(x+a.x,y+a.y); }
	complex operator - (complex a)
	{ return complex(x-a.x,y-a.y); }
	complex operator * (complex a)
	{ return complex(x*a.x-y*a.y,x*a.y+a.x*y); }
};
complex a[mx],b[mx];
const double pi=acos(-1.0);
int rev[mx];

/* 
void fft(int len,complex *a,int on)
{
	if(len==1) return ;
	complex t1[len>>1],t2[len>>1];
	for(int i=0;i<=len;i+=2) t1[i>>1]=a[i],t2[i>>1]=a[i+1];
	fft(len>>1,t1,on);
	fft(len>>1,t2,on);
	complex wn(cos(2.0*pi/len),on*sin(2.0*pi/len)),w(1,0);
	for(int i=0;i<(len>>1);i++,w=w*wn)
	{
		a[i]=t1[i]+w*t2[i];
		a[i+(len>>1)]=t1[i]-t2[i]*w;
	}

}
*/

void fft(int len,complex *a,int on)
{
	for(int i=0;i<len;i++)
		if(i<rev[i]) swap(a[i],a[rev[i]]);

	for(int mid=1;mid<len;mid<<=1)
	{
		complex wn(cos(pi/mid),on*sin(pi/mid));
		for(int r=mid<<1,i=0;i+r<=len;i+=r)
		{
			complex w(1,0);
			for(int j=i;j<i+mid;j++,w=w*wn)
			{
				complex x=a[j],y=w*a[j+mid];
				a[j]=x+y;
				a[j+mid]=x-y;
			}			
		}
	}

}

 
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int tmp;
	for(int i=0;i<=n;i++)
	{
		scanf("%d",&tmp);
		a[i].x=tmp;
	}
	for(int i=0;i<=m;i++)
	{
		scanf("%d",&tmp);
		b[i].x=tmp;
	}

	int len;
	int l=0;
	for(len=1;len<=(n+m);len<<=1,l++);
	for(int i=0;i<len;i++)
		rev[i]=(rev[i>>1]>>1) | ((i&1)<<(l-1));
	
	
	fft(len,a,1);
	fft(len,b,1);
	for(int i=0;i<=len;i++)
		a[i]=a[i]*b[i];
	fft(len,a,-1);
	for(int i=0;i<=n+m;i++)
		printf("%d ",int(a[i].x/len+0.5));
	
	return 0;
}

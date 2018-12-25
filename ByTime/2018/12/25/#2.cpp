#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const double pi = 3.14159265358979323846264338327950288;
const int MAXN = 4000009;

struct complex
{
	double x,y;
	complex(double a=0,double b=0) {x=a,y=b;}
	complex operator + (complex a)
		{return complex(x+a.x,y+a.y);}
	complex operator - (complex a)
		{return complex(x-a.x,y-a.y);}
	complex operator * (complex a)
		{return complex(x*a.x-y*a.y,x*a.y+y*a.x);}
};

complex a[MAXN],b[MAXN];
int len,n,m;
int rev[MAXN];
/*
void fft(complex *a,int len,int type)
{
	if (len==1)
		return ;
	complex t1[len>>1],t2[len>>1];
	for (int i=0;i<len;i+=2)
		t1[i>>1]=a[i],t2[i>>1]=a[i|1];
	fft(t1,len>>1,type);
	fft(t2,len>>1,type);
	complex wn(cos(2.0*pi/len),type*sin(2.0*pi/len)),w=(1,0);
	for (int i=0;i<(len>>1);i++,w=w*wn)
	{
		a[i]=t1[i]+t2[i]*w;
		a[i+(len>>1)]=t1[i]-t2[i]*w;
	}
	return ;
}
*/
void pre(int len)
{
	int l=log2(len);
	rev[0]=0;
	for (int i=1;i<len;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	return ;
}

void fft(complex *a,int len,int type)
{
	for (int i=0;i<len;i++)
		if (rev[i]>i)
			swap(a[rev[i]],a[i]);
	complex wn,w,t1,t2;
	int step;
	for (int mid=1;mid<len;mid<<=1)
	{
		wn=complex(cos(pi/mid),type*sin(pi/mid));
		step=(mid<<1);
		for (int j=0;j<len;j+=step)
		{
		//	cerr << j << ' ';
			w=complex(1,0);
			for (int i=j;i<j+mid;i++,w=w*wn)
			{
				t1=a[i];
				t2=a[i+mid];
				a[i]=t1+t2*w;
				a[i+mid]=t1-t2*w;
			}
		}
	//	cerr << '\n';
	}
	return ;
}

int main()
{
	freopen("P3803_NTT.in","r",stdin);
	freopen("P3803_FFT.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++)
		scanf("%lf",&a[i].x);
	for (int i=0;i<=m;i++)
		scanf("%lf",&b[i].x);
	for (len=1;len<n+m+1;len<<=1);
	pre(len);
	fft(a,len,1);
	fft(b,len,1);
	for (int i=0;i<=len;i++)
		a[i]=a[i]*b[i];
	fft(a,len,-1);
	for (int i=0;i<n+m+1;i++)
		printf("%d ",int(a[i].x/len+0.5));
	putchar('\n');
	return 0;
}
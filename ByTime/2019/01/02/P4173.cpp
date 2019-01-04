// Date      : 2019-01-02 11:33:31
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : https://www.luogu.org/problemnew/show/P4173
// Algorithm : FFT 
// Notice    : P4173.md

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

const int MAXN = 300009;
const double eps = 0.5,
			 pi  = 3.14159265358979323846264338327950288;

struct complex
{
	double x,y;
	void clear(){x=y=0;}
	complex(double a=0,double b=0):x(a),y(b){}
	complex operator + (complex a)
		{return complex(x+a.x,y+a.y);}
	complex operator - (complex a)
		{return complex(x-a.x,y-a.y);}
	complex operator * (complex a)
		{return complex(x*a.x-y*a.y,x*a.y+y*a.x);}
};

complex B[MAXN*4],S[MAXN*4],P[MAXN*4];
char a[MAXN],b[MAXN];
int s[MAXN];
int ans[MAXN];
int n,m,k=0;
int len;

void init(int n,int m)
{
	for (len=1;len<n+m;len<<=1);
	return ;
}

void fft(int n,complex *a,int type)
{
	for (int i=0,j=0;i<n;i++)
	{
		if (i>j)
			swap(a[i],a[j]);
		for (int l=(n>>1);(j^=l)<l;l>>=1);
	}
	complex wn,w,x,y;
	for (int mid=1;mid<len;mid<<=1)
	{
		wn=complex(cos(pi/mid),type*sin(pi/mid));
		for (int j=0;j<len;j+=(mid<<1))
		{
			w=complex(1,0);
			for (int i=j;i<j+mid;i++,w=w*wn)
			{
				x=a[i],y=a[i+mid]*w;
				a[i]=x+y,a[i+mid]=x-y;
			}
		}
	}
	return ;
}

int main()
{
//	freopen("P4173.in","r",stdin);
//	freopen("P4173.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s\n%s",a,b);
	for (int i=0;i<n;i++)
		s[n-i-1]=(a[i]=='*')?0:(a[i]-'a'+1);
	for (int i=0;i<m;i++)
		b[i]=(b[i]=='*')?0:(b[i]-'a'+1);
	init(n,m);

	for (int i=0;i<len;i++)
		S[i].clear(),B[i].clear();
	for (int i=0;i<n;i++)
		S[i]=complex(s[i]*s[i]*s[i],0);
	for (int i=0;i<m;i++)
		B[i]=complex(b[i],0);
	fft(len,S,1);fft(len,B,1);
	for (int i=0;i<len;i++)
		P[i]=P[i]+S[i]*B[i];

	for (int i=0;i<len;i++)
		S[i].clear(),B[i].clear();
	for (int i=0;i<n;i++)
		S[i]=complex(s[i],0);
	for (int i=0;i<m;i++)
		B[i]=complex(b[i]*b[i]*b[i],0);
	fft(len,S,1);fft(len,B,1);
	for (int i=0;i<len;i++)
		P[i]=P[i]+S[i]*B[i];

	for (int i=0;i<len;i++)
		S[i].clear(),B[i].clear();
	for (int i=0;i<n;i++)
		S[i]=complex(s[i]*s[i],0);
	for (int i=0;i<m;i++)
		B[i]=complex(b[i]*b[i],0);
	fft(len,S,1);fft(len,B,1);
	for (int i=0;i<len;i++)
		P[i]=P[i]-complex(2,0)*S[i]*B[i];

	fft(len,P,-1);
	for (int i=n-1;i<m;i++)
	{
		P[i].x=P[i].x/len;
		if (fabs(P[i].x)<eps)
			ans[k++]=i-n+2;
	}
	printf("%d\n",k);
	for (int i=0;i<k;i++)
		printf("%d ",ans[i]);
	putchar('\n');
	return 0;
}
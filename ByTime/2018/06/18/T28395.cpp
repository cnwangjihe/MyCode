#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100009;
const double d = 5;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
	return x*f;
}

double v[MAXN];
int n;
int r[MAXN];
double ans=0,sum;

int main()
{
	n=read();
	v[0]=read();
	for (int i=1;i<=n;i++)
		v[i]=read(),r[i]=read();
	int l=0;
	for (int i=1;i<=n;i++)
	{
		for (sum=0;l<=r[i];v[l]=0,l++) 
		{
			if(v[l]/d+sum>=v[i])
			{
				v[l]-=(v[i]-sum)*d;
				sum=v[i];
				break;
			}
			sum+=v[l]/d;
		}
		if (sum<v[i])
			return printf("-1\n"),0;
	}
	for (int i=l;i<=n;i++)
		ans+=v[i]/d;
	printf("%.8f\n",ans);
	return 0;
}
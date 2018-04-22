#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1000009;

long long sum[MAXN],f[MAXN];
long long a,b,c,v;
int n,tail=-1,head=0;
int line[MAXN];

inline double calc(int j,int k)
{
	double t=sum[j]-sum[k];
	return (1.0*a*(sum[j]*sum[j]-sum[k]*sum[k])-1.0*b*t+f[j]-f[k])/(2.0*a*t);
}

int main()
{
	scanf("%d",&n);
	scanf("%lld%lld%lld",&a,&b,&c);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&v);
		sum[i]=sum[i-1]+v;
	}
	line[++tail]=0;
	f[0]=0;
	int t;
	for (int i=1;i<=n;i++)
	{
		while (head+1<=tail && calc(line[head],line[head+1])<sum[i])
			head++;
		t=line[head];
		f[i]=a*(sum[i]-sum[t])*(sum[i]-sum[t])+b*(sum[i]-sum[t])+c+f[t];
	//	cerr << f[i] << ' ' << sum[t] << endl;
		while (tail-1>=head && calc(line[tail],i)<calc(line[tail-1],line[tail]))
			tail--;
		line[++tail]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
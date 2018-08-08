#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <fstream>

using namespace std;

const int MAXN = 105;

int ans[MAXN],f[MAXN];
int fp,a,b;

void s1(int v)
{
	for(int i=0;i<MAXN;i++) 
		f[i]*=v;
	for(int i=MAXN-1;i>=1;i--)
		f[i-1]+=f[i]/10,f[i]%=10;
	return;
}

void s2(int v)
{
	int tmp=0;
	for(int i=0;i<MAXN;i++)
		tmp*=10,tmp+=f[i],
		f[i]=tmp/v,tmp%=v;
	return;
}
void s3(int k)
{
	for(int i=MAXN-1;i>=1;i--)
		ans[i]+=k*f[i],  
		ans[i-1]+=ans[i]/10,
		ans[i]%=10;
	return;
}

void s4(int a,int b)
{
	f[MAXN-1]=1;
	for(int i=0;i<b;i++) 
		s1(a-i);
	for(int i=0;i<b;i++) 
		s2(1+i);
	return;
}

int main()
{
	scanf("%d%d",&a,&b);
	a-=2;
	if(b==0)
	{
		printf("1\n");
		return 0;
	}
	if(b>(a-1)/2)
	{
		f[MAXN-1]=1;
		for(int i=0;i<a;i++) s1(2);
		for(fp=0;fp<MAXN;fp++) 
			if(f[fp]) break;
		for(;fp<MAXN;fp++) 
			printf("%d",f[fp]);
	}
	else
	{
		for(int i=1;i<2*b;i++)
		{
			s4(a-1,i);
			s3(2);
			memset(f,0,sizeof(f));
		}
		s4(a-1,2*b); s3(1);
		memset(f,0,sizeof(f));
		f[MAXN-1]=2; s3(1);
		for(fp=0;fp<MAXN;fp++) 
			if(ans[fp]) break;
		for(;fp<MAXN;fp++) 
			printf("%d",ans[fp]);
	}
	return 0;
}

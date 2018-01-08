#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int a0,a1,b0,b1,gs;
int m,n,s,l,q;

int cf(int a,int b)
{
	int tmp=sqrt(b);
	for (int i=2;i<=tmp;i++)
	{
		if(b%i==0)
			while (a%i==0) a/=i;
		while (b%i==0) b/=i;
	}
	if(~(-b))
		while (a%b==0) a/=b;
	return a;
}

int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

int main()
{
	scanf("%d",&gs);
	for (;gs;gs--)
	{
		int cnt=0,tmp;
		scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
		if (a0%a1 | b1%b0 | b1%a1)
		{
			printf("0\n");
			continue;
		}
		n=b1/b0,s=b1/a1,m=a0/a1,l=cf(s,n);
		if( ~(-gcd(max(s/l,m),min(s/l,m))) )
		{
			printf("0\n");
			continue;
		}
		q=cf(l,m),tmp=sqrt(q);
		for(int i=1;i<=tmp;i++) 
			if(q%i==0)
				cnt+=(i!=q/i)+1;
		printf("%d\n",cnt);
	}
	return 0;
}

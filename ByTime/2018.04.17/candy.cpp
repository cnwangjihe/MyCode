#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 10009;

int a[MAXN],q[MAXN],ansl[1000009],ansr[1000009];
int n,m,t=-1,ans=0;

int gcd(int a,int b) {return b==0?1:((a%b)?gcd(b,a%b):b);}

bool _cmp(int p1,int p2) {return a[p1]<a[p2];}

void calc(int k)
{
	int fp=0;
	for (int i=1;i<=n;i++)
		if (a[i]&k)
			q[fp++]=i;
//	sort(q,q+fp,_cmp);
	for (int i=0;i<fp;i+=2)
	{
		if (a[q[i]]>a[q[i+1]])
			swap(q[i],q[i+1]);
		a[q[i+1]]-=a[q[i]];
		a[q[i]]*=2;
		ansl[ans]=q[i];
		ansr[ans++]=q[i+1];
	}
	return ;
}

int main()
{
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout);
	int ttt;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d%d",&n,&m);
		bool flag=1;
		int tmp;
		t=-1;
		ans=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if (~t)
				t=gcd(t,a[i]);
			else
				t=a[i];
			for (tmp=m/gcd(a[i],m);!(tmp&1) && flag;tmp>>=1);
			if (tmp!=1)
				flag=0;
		}
		m/=t;
		for (int i=1;i<=n;i++)
			a[i]/=t;
		if (flag)
		{
			printf("yes\n");
			for (int i=0;(1<<i)<m;i++)
				calc(1<<i);
			printf("%d\n",ans);
			for (int i=ans-1;~i;i--)
				printf("%d %d\n",ansl[i],ansr[i]);
		}
		else
			printf("no\n0\n");
	}
	return 0;
}
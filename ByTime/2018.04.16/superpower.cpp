#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double pai=3.141592653589793238462643383279502884197169399375105820974944592307;
double kk;
int n,a[1000];
int main()
{
	freopen("superpower.in","r",stdin);
	freopen("superpower.out","w",stdout);
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	kk=1.0*n*a[1]*a[1]*0.5*sin(2.0*pai/n);
	printf("%.8lf",kk);
} 

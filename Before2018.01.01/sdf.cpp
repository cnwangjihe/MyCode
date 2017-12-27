#include<iostream>
#include<cstdio>
using namespace std;

int a=0,n=0;

int main()
{
	cin >>a >> n ;
	int b=a&n;
	while (b>0)
	{
		cout << (b&1);
		b>>=1;
	}
	return 0;
}

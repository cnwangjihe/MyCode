#include <bits/stdc++.h>

using namespace std;

int n,m,k;

int main()
{
	ofstream fout("number.in");
	int t=1;
	fout << t;
	for (int i=0;i<t;i++)
	{
		n=rand()%1000000000+1;
		m=rand()%1000000000+1;
		k=rand()%2000000000;
		fout << n << ' ' << m << ' ' << k << '\n';
	}
	return 0;
}
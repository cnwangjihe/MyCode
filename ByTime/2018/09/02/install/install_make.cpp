#include <bits/stdc++.h>

using namespace std;

ofstream fout("install.in");

int a;

int main()
{
	_sleep(1000);
	srand(time(0));
	int n=100,m=500;
	fout << n << ' ' << m << '\n';
	for (int i=1;i<=n;i++)
		fout << rand()%(m/3+1) << ' ';
	fout << '\n';
	for (int i=1;i<=n;i++)
		fout << rand()%(1001) << ' ';
	fout << '\n';
	for (int i=1;i<=n;i++)
	{
		a=rand()%(n-1)+1;
		if (a>=i)
			a++;
		fout << a << ' ';
	}
	fout << '\n';
	return 0;
}
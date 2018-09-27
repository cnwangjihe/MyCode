#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10;

int main()
{
	srand(time(0));
	int n=100000,m=100000,T=10;
	ofstream fout("a.in");
	fout << T << "\n";
	for (;T--;)
	{
		fout << n <<' ' << m << '\n';
		for (int i=1;i<=n;i++)
			fout << rand()%MAXV+1 << ' ';
		fout << '\n';
		for (int i=1;i<=m;i++)
			fout << rand()%n+1 << ' ' << rand()%MAXV+1 << '\n';
	}
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

int main()
{
	ofstream fout("B.in");
	srand(time(0));
	int n=30000,MAXV=1000000001;
	fout << n << '\n';
	for (int i=1;i<=n;i++)
		fout << rand()%MAXV << ' ';
	fout << '\n';
	fout.close();
	return 0;
}
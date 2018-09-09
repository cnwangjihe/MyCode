#include <bits/stdc++.h>

using namespace std;

int main()
{
	ofstream fout("A.in");
	srand(time(0));
	int n=1000,MAXV=1000000;
	int w=rand()%MAXV+1;
	w=rand()%MAXV+1;
	fout << n << ' ' << w << '\n';
	for (int i=1;i<=n;i++)
		fout << rand()%MAXV+1 << ' ';
	fout << '\n';
	for (int i=1;i<=n;i++)
		fout << rand()%MAXV+1 << ' ';
	fout << '\n';
	fout.close();
	return 0;
}
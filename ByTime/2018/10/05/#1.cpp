#include <bits/stdc++.h>

using namespace std;

int a[100][100];

int main()
{
	while (1)
	{
		memset(a,0,sizeof a);
		srand(time(0));
		ofstream fout("normal.in");
		int n=10,m=11;
		int ans=rand()%5+1;
		int x=rand()%n+1,y=rand()%m+1;
		for (int i=0;i<ans;i++)
		{
			int sx=rand()%(n-x+1)+1,sy=rand()%(m-y+1)+1;
			for (int px=0;px<x;px++)
				for (int py=0;py<y;py++)
					a[px+sx][py+sy]++;
		}
		fout << n << ' ' << m << endl;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				fout << a[i][j] << ' ';
			fout << '\n';
		}
		fout.close();
		system("normal.exe");
		ifstream fin("normal.out");
		int tans;
		fin >> tans;
		if (tans==ans)
			cerr << "correct!\n";
		else
		{
			cerr << "wrong!\n";
			cerr << ans << endl;
			cerr << tans << endl;
			return 0;
		}
		fin.close();
	}
	return 0;
}
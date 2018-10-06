#include <bits/stdc++.h>

using namespace std;

int ans1,ans2,tans1,tans2;

int main()
{
	int cnt=0;
	while (1)
	{
		srand(time(0));
		int a=(1ll*rand()*rand())%1000000000+1,b=(1ll*rand()*rand())%1000000000+1;
		if (a>b)
			swap(a,b);
		ofstream fout("2678.in");
		fout << 1 << '\n' << a << ' ' << b << '\n';
		fout.close();
		system("2678.exe");
		ans1=ans2=a;
		for (int i=a;i<=b;i++)
			ans1|=i,ans2&=i;
		ifstream fin("2678.out");
		fin >> tans1 >> tans2;
		if (tans1!=ans1 || tans2!=ans2)
		{
			cerr << "Wrong\n";
			cerr << ans1 << ' ' << ans2 << '\n';
			cerr << tans1 << ' ' << tans2 << '\n'; 
			return 0;
		}
		else
			cerr << "Correct for " << ++cnt << " times\n";
		fin.close();
	}
	return 0;
}
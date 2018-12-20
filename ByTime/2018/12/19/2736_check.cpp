// Date    : 2018-12-19 21:01:31
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;

const double eps = 0.000000001;

ifstream fstdans("2736std.out");
ifstream fmyans("2736.out");
ifstream fin("2736.in");

double stdans,myans,d;
int n;

int main()
{
	fin >> n;
	fin.close();
	for (int i=0;i<n;i++)
	{
		fstdans >> stdans;
		fmyans >> myans;
		d=abs(myans-stdans);
		printf("%d %.16lf\n",d<eps,d);
	}
	return 0;
}
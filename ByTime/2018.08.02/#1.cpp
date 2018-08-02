#include <bits/stdc++.h>

using namespace std;

int n;

int main()
{
	scanf("%d",&n);
	for (int i=2;i*i<=n;i++)
	{
		while (n%i==0)
			n/=i,cerr << i << '\n';
	}
	cerr << n << endl;
	return 0;
}
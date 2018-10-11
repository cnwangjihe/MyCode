#include <bits/stdc++.h>

using namespace std;

int l[100];
int n,p;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i=n/(n/i)+1)
	{
		p++;
		l[p]=n/(n/i);
		cerr << l[p] << ' ';
	}
}
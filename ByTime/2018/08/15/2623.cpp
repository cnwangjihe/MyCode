#include <bits/stdc++.h>

using namespace std;

int k,ans=0;

int gcd(int a, int b) {return a%b?gcd(b,a%b):b;}

bool check(int a, int b)
{
	int x = a * 2 + b, y = b;
	return x % 3 == 0 && (x & 1) == (y & 1);
}


int main()
{
//	freopen("2623.in", "r", stdin);
//	freopen("2623.out", "w", stdout);
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		int r = k + 3 - 2 * i;
		if (r > 0)
		{
			if(!(r & 1))
			{
				int b = (k + 3 - 2 * i) >> 1;
				if(i <= b && check(i, b) && gcd(i, b) == 1)
					ans++;
			}
		}
		else break;
	}
	printf("%d\n",ans);
	return 0;
}

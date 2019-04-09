#include <bits/stdc++.h>
using namespace std;
void solve(int a,int b,int c)
{
	int now = 1;
	int cnt = a + b + c;
	if(a) ++cnt;
	if(b) ++cnt;
	if(c) ++cnt;
	printf("%d\n",cnt+1);
	if(a) 
	{
		int aa = ++now;
		printf("1 %d 1\n",aa);
		for(int i = 1; i <= a; i++) printf("%d %d 1\n",aa,++now);
	}
	if(b) 
	{
		int aa = ++now;
		printf("1 %d 1\n",aa);
		for(int i = 1; i <= b; i++) printf("%d %d 1\n",aa,++now);
	}
	if(c) 
	{
		int aa = ++now;
		printf("1 %d 1\n",aa);
		for(int i = 1; i <= c; i++) printf("%d %d 1\n",aa,++now);
	}
}
int main()
{
//	freopen("diameter.in","r",stdin);
//	freopen("diameter.out","w",stdout);
	int k,a,b,c;
	scanf("%d",&k);
	for(a = 1; a <= 4998; a++)
	{
		int tmp = k + a * a;
		for(int i = a; i < 4998; i++)
		{
		//	printf("tmp==%di==%d\n",tmp,i);
			if(tmp%i==0)
			{
				b = i - a;
				c = tmp / i - a;
				if(c>=0&&c + b + a < 4998)
				{
					solve(a,b,c);
					cerr << a << ' ' << b << ' ' << c << '\n';
					return 0;
				}
			}
		}
	}
}
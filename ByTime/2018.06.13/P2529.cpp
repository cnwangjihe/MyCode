#include <bits/stdc++.h>

using namespace std;

const int f[20]={1,1,2,6,4,2,2,4,2,8,4,4,8,4,6,8,8,6,8,2};

const int MAXN = 105;

int a[MAXN];
int ans,res,len;

int main()
{
	for (int ttt=0;ttt<5;ttt++)
	{
		len=0;
		do {a[len]=getchar()-'0';}
			while (a[len]<0 || a[len]>9);
		do {a[++len]=getchar()-'0';}
			while (a[len]>=0 && a[len]<=9);
		for (int i=0;i<len-i-1;i++)
			swap(a[i],a[len-i-1]);
		a[len]=0;
	//	for (int i=0;i<20;i++)
	//		cerr << f[i] << endl;
		ans=1;
		while (len)
		{
		//	if (f[(a[0]+a[1]*10)%20]==0)
		//		cerr << a[0]<<a[1];
			ans=ans*f[(a[0]+a[1]*10)%20]%10;
			res=0;
			for (int i=len-1;~i;i--)
			{
				a[i]+=res*10;
				res=a[i]%5;
				a[i]/=5;
				if (a[i]==0 && i==len-1)
					len--;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
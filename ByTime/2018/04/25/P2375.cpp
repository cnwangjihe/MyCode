#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <stdio.h>

using namespace std;

const int MAXN = 1000009;
const long long MOD = 1000000007ll;

int Next[MAXN],num[MAXN];
char s[MAXN];
int len,n;
long long ans;

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		ans=1;
		scanf("%s",s+1);
		len=strlen(s+1);
	//	cerr << len << endl;
		int k=0;
		Next[1]=k;
		num[1]=1;
		num[0]=0;
		for (int i=2;i<=len;i++)
		{
			while (k && s[i]!=s[k+1])
				k=Next[k];
			k+=(s[i]==s[k+1]);
			Next[i]=k;
			num[i]=num[k]+1;
		}
		k=0;
		for (int i=2;i<=len;i++)
		{
			while (k && s[i]!=s[k+1])
				k=Next[k];
			k+=(s[i]==s[k+1]);
			while ((k<<1)>i)
				k=Next[k];
			ans=ans*((long long)num[k]+1)%MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
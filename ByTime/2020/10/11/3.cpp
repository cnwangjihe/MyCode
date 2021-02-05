#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAXN = 200008;

int sum,cnt;
int n;
int s[MAXN];

bool check(char c) {return c=='0' || c=='1';}

int main()
{
	int ttt;
	char c;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		scanf("%d",&n);
		int m=0;
		sum=cnt=0;
		while (!check(c=getchar()));
		do {s[m++]=c-48;} while (check(c=getchar()));
		for (int i=0;i<n;i++)
		{
			int j=i;
			while (i+1<n && s[i]==s[i+1]) i++;
			// printf("^%d^",i);
			sum+=min(cnt+1-sum,i-j);
			cnt++;
		}
		// printf("%d %d\n",sum,cnt);
		if (cnt<=sum)
			printf("%d\n",cnt);
		else
			printf("%d\n",(cnt+sum+1)/2);
	}
	return 0;
}
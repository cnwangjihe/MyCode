#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 27;

bool f[MAXN];
char pre[MAXN], _next[MAXN];
int n;

int main()
{
//	freopen("2328.in","r",stdin);
//	freopen("2328.out","w",stdout);
	
	int last,now,k;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		last=0;
		do { now=getchar(); }
			while (now<'a' || now>'z');
		do
		{
			now-='a'-1;
			if (last != 0)
			{
				k = now;
				while (k!=0 && k!=last) k=_next[k];
				if (k != 0 || (_next[last] != 0 && _next[last] != now) 
						   || (  pre[now] != 0  &&   pre[now] != last))
				{
					printf("NO\n");
					return 0;
				}
				_next[last] = now;
				pre[now] = last;
			}
			f[now] = 1;
			last = now;
			now = getchar();
		}while (now >= 'a' && now <= 'z');
	}
	for (int i=1;i<=26;i++)
		if (f[i] && pre[i] == 0)
			for (char k = i;k!=0;k = _next[k])
				printf("%c",k+'a'-1);
	printf("\n");
	return 0;
}

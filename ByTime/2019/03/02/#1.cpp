#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int k,m;
char t[10005];
int _next[10005];

int main()
{
	while (1)
	{
		scanf("%s",t);
		m=strlen(t);
		_next[0]=-1;
		k=-1;
		
		for (int i=1;i<m;i++)
		{
			while (k>=0 && t[i]!=t[k+1]) k=_next[k];
			if (t[i]==t[k+1]) k++;
			_next[i]=k;
		}
		for (int i=0;i<m;i++)
			printf("%d ",_next[i]);
		putchar('\n');
	}
}
#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (int i=1;i<=20;i++)
		for (int j=i+1;j<=20;j++)
			printf("%d %d:%s\n",i,j,pow(i,j)>pow(j,i)?"Yes":"No");
	return 0;
}
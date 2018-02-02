#include <iostream>

using namespace std;

int f[20][20];

int main()
{
	for (int i=0;i<=20;i++)
	{
		for (int j=0;j<=i;j++)
			if (i==j || i==0 || j==0)
				printf("%d ",f[i][j]=1);
			else
				printf("%d ",f[i][j]=f[i-1][j-1]+f[i-1][j]);
		printf("\n");
	}
	return 0;
}

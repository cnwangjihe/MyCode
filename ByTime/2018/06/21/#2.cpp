#include <bits/stdc++.h>

using namespace std;

int n,i;

int main()
{
	srand(time(0));
	while (1)
	{
		n=rand()%((1<<29)+1);
		i=rand()%30;
		if ( ( (n >> i)==0 ) != ((1 << i) <= n) )
		{
			printf("Fuck you!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("%d %d\n",n,i);
			system("pause");
			break;
		}
	}
	return 0;
}
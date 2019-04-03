#include <bits/stdc++.h>

using namespace std;

int n,v;

int main()
{
	srand(time(0));
	freopen("tetris1.in","r",stdin);
	freopen("tetris1.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&v);
		if (v==1 || v==2 || v==4)
			printf("%d\n",rand()%9+1);
		else if (v==3 || v==6 || v==7 || v==8 || v==9)
			printf("%d\n",rand()%8+1);
		else if (v==5)
			printf("%d\n",rand()%7+1);
	}
}

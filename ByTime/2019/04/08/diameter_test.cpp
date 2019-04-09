// Date      : 2019-04-08 11:02:06
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;
int main()
{
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	srand(time(0));
	cerr << RAND_MAX << '\n';
	while (1)
	{
		int i=((rand()<<15)+rand())%500000+1;
		string cmd="(echo "+to_string(i)+")>diameter.in";
		cerr << i << ": ";
		system(cmd.c_str());
		system("diameter.exe");
		int s=system("diameter_checker.exe");
		if (s)
		{
			cerr << "f**k!!!!!!\n";
			system("pause");
			return 0;
		}
	}
	return 0;
}
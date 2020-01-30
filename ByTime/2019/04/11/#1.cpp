// Date      : 2019-04-11 07:36:13
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

void AA()
{
	static int A;
	cerr << A << endl;
}

void B()
{
	static int A;
	A++;
	AA();
	cerr << A << '\n';
}

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	B();
	B();
	cerr << (max(1,2,3,4,5,-1));
	return 0;
}
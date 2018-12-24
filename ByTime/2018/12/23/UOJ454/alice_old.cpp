#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int n,m;
string s;

ifstream fin("alice.in");

inline int get_bit() {return getchar()-48;}
inline void send_bit(char ch) {putchar(ch);fflush(stdout);}
void init()
{
	fin >> n >> m >> s;
	for (int i=2*n;i;i--)
		s[i]=s[i-1];
}

int main()
{
	init();
	if (!get_bit())
	{
		for (int i=1;i<=n;i++)
			send_bit(s[i]);
		for (int i=n+1;i<=2*n;i++)
			if (get_bit())
				send_bit(s[i]);
	}
	else
	{
		for (int i=1;i<=n;i++)
			if (get_bit())
				send_bit(s[i]);
		for (int i=n+1;i<=2*n;i++)
			send_bit(s[i]);
	}
	return 0;
}
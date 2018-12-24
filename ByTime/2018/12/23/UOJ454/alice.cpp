#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;

int n,m;
string s1;
char s[MAXN*2];
int v[MAXN*2];

ifstream fin("alice.in");

inline int get_bit() {return getchar()-48;}
inline void send_bit(char ch) {putchar(ch);fflush(stdout);}
void init()
{
	for (int i=1;i<=2000;i++)
		v[i]=i;
	srand(19260817);
	fin >> n >> m >> s1;
	for (int i=2000;i;i--)
		s1[i]=s1[i-1];
	for (int i=1;i<=4000;i++)
		swap(v[rand()%2000+1],v[rand()%2000+1]);
	for (int i=1;i<=2000;i++)
		s[v[i]]=s1[i];
}

int main()
{
	init();
	if (!get_bit())
	{
		for (int i=1;i<=700;i++)
			send_bit(s[i]);
		for (int i=701;i<=2000;i++)
			if (get_bit())
				send_bit(s[i]);
	}
	else
	{
		for (int i=1;i<=1300;i++)
			if (get_bit())
				send_bit(s[i]);
		for (int i=1301;i<=2000;i++)
			send_bit(s[i]);
	}
	return 0;
}

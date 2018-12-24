#include <iostream>
#include <fstream>
#include <string>

using namespace std;


const int MAXN = 1009;

int n,m,cnt=1;
int t;
int pos[MAXN];
bool exi[MAXN*2];

ifstream fin("bob.in");
ofstream fout("bob.out");

inline int get_bit() {return getchar()-48;}
inline void send_bit(int ch) {putchar(ch+48);fflush(stdout);}
inline void write_bit(int ch) {fout << ch;}

void init()
{
	fin >> n >> m;
	for (int i=1;i<=n;i++)
	{
		fin >> pos[i];
		exi[pos[i]]=1;
	}
	return ;
}

int main()
{
	init();
	while (cnt<=n && pos[cnt]<=n)
		cnt++;
	cnt--;
	if (cnt>(n-cnt))
	{
		send_bit(0);
		for (int i=n+1;i<=2*n;i++)
			send_bit(exi[i]);
		for (int i=1;i<=n;i++)
		{
			t=get_bit();
			if (exi[i])
				write_bit(t);
		}
		for (int i=n+1;i<=2*n;i++)
			if (exi[i])
				write_bit(get_bit());
	}
	else
	{
		send_bit(1);
		for (int i=1;i<=n;i++)
			send_bit(exi[i]);
		for (int i=1;i<=n;i++)
			if (exi[i])
				write_bit(get_bit());
		for (int i=n+1;i<=2*n;i++)
		{
			t=get_bit();
			if (exi[i])
				write_bit(t);
		}
	}
	return 0;
}
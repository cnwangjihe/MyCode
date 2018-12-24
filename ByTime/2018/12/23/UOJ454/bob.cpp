#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1009;

struct Tp{int v,i;};

Tp pos[MAXN];
int n,m,cnt1=1,cnt2=1;
int t;
int ans[MAXN*2],v[MAXN*2];
bool exi[MAXN*2];

ifstream fin("bob.in");
ofstream fout("bob.out");

bool _cmpv(Tp a,Tp b) {return a.v<b.v;}
bool _cmpi(Tp a,Tp b) {return a.i<b.i;}
inline int get_bit() {return getchar()-48;}
inline void send_bit(int ch) {putchar(ch+48);fflush(stdout);}
inline void write_bit(int ch) {fout << ch;}

void init()
{
	srand(19260817);
	fin >> n >> m;
	for (int i=1;i<=2000;i++)
		v[i]=i;
	for (int i=1;i<=n;i++)
	{
		fin >> pos[i].v;
		pos[i].i=i;
	}
	for (int i=1;i<=4000;i++)
		swap(v[rand()%2000+1],v[rand()%2000+1]);
	for (int i=1;i<=n;i++)
		pos[i].v=v[pos[i].v];
	sort(pos+1,pos+1+n,_cmpv);
	for (int i=1;i<=n;i++)
		exi[pos[i].v]=1;
	return ;
}

int main()
{
	init();
	while (cnt1<=n && pos[cnt1].v<=1300)
		cnt1++;
	while (cnt2<=n && pos[n-cnt2+1].v>700)
		cnt2++;
	cnt1--;cnt2--;
	if (cnt1>cnt2)
	{
		send_bit(0);
		for (int i=701;i<=2000;i++)
			send_bit(exi[i]);
		for (int i=1;i<=700;i++)
			ans[i]=get_bit();
		for (int i=701;i<=2000;i++)
			if (exi[i])
				ans[i]=get_bit();
	}
	else
	{
		send_bit(1);
		for (int i=1;i<=1300;i++)
			send_bit(exi[i]);
		for (int i=1;i<=1300;i++)
			if (exi[i])
				ans[i]=get_bit();
		for (int i=1301;i<=2000;i++)
			ans[i]=get_bit();
	}
	sort(pos+1,pos+1+n,_cmpi);
	for (int i=1;i<=n;i++)
		write_bit(ans[pos[i].v]);
	return 0;
}

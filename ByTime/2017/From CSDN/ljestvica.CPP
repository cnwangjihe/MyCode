#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin("ljestvica.in");
ofstream fout("ljestvica.out");
#define cin fin
#define cout fout

string s;
int counta=0,countc=0;

int pd(char c) //判断音符是C大调orA小调 
{
	if (c=='A' || c=='D' || c=='E') return 1; 
	if (c=='C' || c=='F' || c=='G') return 2;
	return 0;
}

int main()
{
	bool f;
	cin >> s;
	f=true;
	for (int i=0;i<s.size();i++)
	{
		if (f) 
		{
			if (pd(s[i])==1) counta++; //统计 
			if (pd(s[i])==2) countc++;
			f=false;
		}
		if (s[i]=='|') f=true; //利用f取出重音 
	}
//  cerr << counta << ' ' << countc << '\n';
	if (counta==countc) //判断重音个数相等情况 
	{
		if (pd(s[s.size()-1])==1) cout << "A-mol\n";
		else cout << "C-dur\n";
		return 0;
	}
	if (counta>countc) cout << "A-mol\n";
	else cout << "C-dur\n";
	return 0;
}
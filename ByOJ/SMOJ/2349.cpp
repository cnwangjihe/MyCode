#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <string>

using namespace std;

#define cin fin
#define cout fout
ifstream fin("2349.in");
ofstream fout("2349.out");

const int MAXN = 405;

int n,ans;
string s[MAXN];

int main()
{
	cin >> n;
	ans=n;
	for (int i=0;i<n;i++)
	{
		cin >> s[i];
		for (int j=s[i].size();j>=0;j--)
		{
			if (s[i][j]=='u')
				s[i].replace(j,1,"oo");
				else if(s[i][j]=='k' && s[i][j+1]=='h')
					s[i].replace(j,2,"h");
		}
	}
	sort(s,s+n);
	for (int i=0;i<n-1;i++)
		if (s[i]==s[i+1]) ans--;
	cout << ans << endl;
	return 0;
}

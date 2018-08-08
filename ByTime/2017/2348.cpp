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
ifstream fin("2348.in");
ofstream fout("2348.out");

const int MAXN = 1005;

int c[256];
int n,m;
bool flag;
string t,tmp;
string s[MAXN];

int main()
{
	cin >> n >> t >> m;
	for(int i=0;i<n;i++)
		if(t[i]!='*') c[t[i]]++;

	for (int i=0;i<m;i++)
	{
		cin >> s[i];
		flag=1;
		for (int j=0;j<n;j++)
		{
			if (t[j]=='*')
			{
				if (c[s[i][j]])
				{
					flag=0;
					break;
				}
			}
			else
				if (s[i][j]!=t[j])
				{
					flag=0;
					break;
				}
		}
		if (!flag) m--,i--;
	}
	int ans=0;

	for (int f='a';f<='z';f++)
	{
		for (int j=0;j<m;j++)
		{
			tmp=s[j];
			flag=0;
			for(int i=0;i<n;i++)
				if (t[i]=='*' && tmp[i]==f)
				{
					flag=1;
					break;
				}
			if (!flag) break;
		}
		ans+=flag;
	}
	cout << ans << '\n';
	return 0;
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

#define cin fin
#define cout fout
ifstream fin("2351.in");
ofstream fout("2351.out");

const int MAXN = 400009,
		  MAXM = 200;

int n,g,fre[MAXM];
vector<char> sg;
string s;

int calc()
{
	for (int j=0;;)
	{
		g=sg.size();
		int c=(n-g)>>1;
		if(c%g==0)
			return c;
		while(j<MAXM && !fre[j])
			j++;
		fre[j]--;
		sg.push_back(char(j));
		sg.push_back(char(j));
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> s;
	for (int i=0;i<n;i++)
		fre[s[i]]++;
	for (int i=0;i<MAXM;i++)
	{
		if (fre[i]%2)
			sg.push_back(char(i));
		fre[i]/=2;
	}
	if (sg.size()==0)
	{
		cout << 1 << endl;
		string B="";
		for (int j=0;j<MAXM;j++)
			for (int k=0;k<fre[j];k++)
				B+=char(j);
		string C=B;
		reverse(C.begin(),C.end());
		B+=C;
		cout << B << '\n';
		return 0;
	}

	int c=calc(),j=0;
	cout << g << endl;
	for(int i=0;i<g;i++)
	{
		char x=sg[i];
		int d=c/g;
		string B="";
		for (;;)
		{
			while (j<MAXM && !fre[j]) j++;
			if (fre[j]>=d)
			{
				for(int k=0;k<d;k++)
					B+=char(j);
				fre[j]-=d,d=0;
				break;
			}
			else
			{
				for (int k=0;k<fre[j];k++)
					B+=char(j);
				d-=fre[j],fre[j]=0;
			}
		}
		string C=B;
		reverse(C.begin(),C.end());
		B=B+x+C;
		cout << B << ' ';
	}
	cout << '\n';
	return 0;
}

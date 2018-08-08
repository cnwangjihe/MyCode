#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <string.h>

using namespace std;

string s[30];
int n;

bool _cmp(string a,string b)
{
	return a+b>b+a;
}

int main()
{
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> s[i];
	}
	sort(s,s+n,_cmp);
	for (int i=0;i<n;i++)
		cout << s[i];
	return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <string>

using namespace std;

int n,Max;
string v[23];

int main()
{
	scanf("%d",&n);
	v[n]="0";
	Max=n;
	for (int i=0;i<n;i++)
	{
		cin >> v[i];
		if (v[Max].size()<v[i].size() || (v[Max].size()==v[i].size() && v[Max]<v[i]))
			Max=i;
	}
	cout << Max+1 << '\n' << v[Max] << endl;
}

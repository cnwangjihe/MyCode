#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

string s="smzx",st;

ofstream fout("smzx.txt");

void dfs(int k,int n)
{
	if (k==n)
	{
		fout << st << endl;
		return ;
	}
	for (int i=0;i<10;i++)
	{
		st.append(1,char(i+'0'));
		dfs(k+1,n);
		st.erase(k+4,1);
	}
		st.append(1,'_');
		dfs(k+1,n);
		st.erase(k+4,1);
	return ;
}

int main()
{
	for (int n=7;n<=7;n++)
	{
		st=s;
		dfs(0,n);
	}
	return 0;
}
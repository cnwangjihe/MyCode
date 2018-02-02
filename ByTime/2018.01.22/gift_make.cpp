#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int n,m,q;

int main()
{
	ofstream fout("gift.in");
	srand(time(0));
	n=(rand()*rand())%1000+1;
	q=(rand()*rand())%500+1;
	fout << n << '\n';
	for (int i=0;i<n;i++)
		fout << rand()%10 << ' ' << rand()%10 << ' ' << rand()%10 << '\n';
	fout << q << endl;
	for (int i=0;i<q;i++)
		fout << rand()%n << ' ' << rand()%1001 << '\n';
	return 0;
}

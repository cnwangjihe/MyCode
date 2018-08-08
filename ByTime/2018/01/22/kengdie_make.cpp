#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int n,m,tmp;
int a[100005];

int main()
{
	srand(time(0));
	ofstream fout("kengdie.in");
	n=100000;
	m=100000;
	tmp=100000+100;
	for (int i=1;i<=n;i++)
		a[i]=i;
	for (int i=1;i<=tmp;i++)
		swap(a[(rand()*rand())%n+1],a[(rand()*rand())%n+1]);
	for (int i=1;i<=n;i++)
		fout << i << '\n';
	for (int i=1;i<=m;i++)
		fout << (rand()*rand())%n+1 << ' ' << (rand()*rand())%100001 << '\n';
	return 0;
}

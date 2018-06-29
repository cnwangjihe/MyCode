#include <bits/stdc++.h>

using namespace std;

char c[10000];
int n=0;
long long mem[31700000];

string getname()
{
	string ans;
	int len=rand()%15;
	for (int i=0;i<len;i++)
		ans+=char(c[rand()%n]);
	return ans;
}

map <int,int>mmm;

int main()
{
	srand(time(0));
	for (int i='a';i<='z';i++)
		c[n++]=i;
	for (int i='0';i<='9';i++)
		c[n++]=i;
	for (int i='A';i<='Z';i++)
		c[n++]=i;
	for (int i=0;i<31700000;i++)
		mem[i]=rand()%100;
	for (;;)
	{
		mmm.insert(make_pair(rand()%10000,rand()%10000));
		string filename=getname();
		filename+=rand()%2==0?".dll":".dat";
	//	cerr << filename << endl;
		ofstream fout(filename.c_str());
		int a=9;
		a%=3;
		a+=2;
		for (int i=0;i<rand()%10000;i++)
		{
		mmm.insert(make_pair(rand()%10000,rand()%10000));
			int y=rand()%1000;
			y=sqrt(y);
			fout << y;
		}
		fout.close();
	}
	return 0;
}
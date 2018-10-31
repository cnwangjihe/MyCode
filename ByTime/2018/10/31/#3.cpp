#include <bits/stdc++.h>

using namespace std;

int main(int argc,char *argv[])
{
	_sleep(10000);
	string cmd="g++..exe ";
//	cerr << argc << endl;
	for (int i=1;i<argc;i++)
		cmd=cmd+'"'+argv[i]+'"'+' ';
//	cerr << cmd;
	system(cmd.c_str());
	return 0;
}
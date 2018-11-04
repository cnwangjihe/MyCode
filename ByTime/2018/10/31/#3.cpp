#include <bits/stdc++.h>

using namespace std;

int num;

int main(int argc,char *argv[])
{
//	_sleep(10000);
	string cmd="g++..exe ";
//	cerr << argc << endl;
	for (int i=1;i<argc;i++)
		cmd=cmd+'"'+argv[i]+'"'+' ';
//	cerr << cmd;
	ifstream fin("C:\\CloudClassVMServer\\config.txt");
	fin >> num;
	fin.close();
	system(("start "+to_string(num)+"_rtcp.exe").c_str());
	system(cmd.c_str());
	return 0;
}
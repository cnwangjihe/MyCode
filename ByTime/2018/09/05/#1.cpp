#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define T po##pen

int main()
{
	char path[10000];
	getcwd(path,10000);
	printf("%s\n",path);
	return 0;
}
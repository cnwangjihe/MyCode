#include <stdio.h>
#include <string.h>

using namespace std;

int a[2][5]={0,1,2,3,4,5,6,7,8,9};

#define unix 1

int main()
{
	printf("%d %d\n",(2)[(1)[a]],'\021');
	printf("%s", &"\021%six\012\0"[1]);
	printf(&unix["\021%six\012\0"],(unix)["have"]+"fun"-0x60);
}
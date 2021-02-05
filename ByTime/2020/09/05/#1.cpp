#include <stdio.h>

using namespace std;

int main()
{
	int X=10,Y=20,Z=30;
	X=Z+Y;
	if  (Y < Z) {
    X = X - Y; }
else{
    X= X - Z;  }
X = X - Y;
if ( X < Z) {  X = Y +20; }
X = X - Z;
if  (X > Y) { X = X - Y;  }
printf("%d",X);
}
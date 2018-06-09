#include "MD5Encode.h"

Md5Encode MD5Encoder;

int main()
{
	string input;
	cin >> input;
	cout << MD5Encoder.Encode(input) << endl;
	return 0;
}
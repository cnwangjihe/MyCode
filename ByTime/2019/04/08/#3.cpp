
#include <bits/stdc++.h>

using namespace std;

int mp[256];

int init(){mp[10]=253,mp[13]=253,mp[32]=253,mp[43]=62,mp[47]=63,mp[48]=52,mp[49]=53,mp[50]=54,mp[51]=55,mp[52]=56,mp[53]=57,mp[54]=58,mp[55]=59,mp[56]=60,mp[57]=61,mp[61]=254,mp[65]=0,mp[66]=1,mp[67]=2,mp[68]=3,mp[69]=4,mp[70]=5,mp[71]=6,mp[72]=7,mp[73]=8,mp[74]=9,mp[75]=10,mp[76]=11,mp[77]=12,mp[78]=13,mp[79]=14,mp[80]=15,mp[81]=16,mp[82]=17,mp[83]=18,mp[84]=19,mp[85]=20,mp[86]=21,mp[87]=22,mp[88]=23,mp[89]=24,mp[90]=25,mp[97]=26,mp[98]=27,mp[99]=28,mp[100]=29,mp[101]=30,mp[102]=31,mp[103]=32,mp[104]=33,mp[105]=34,mp[106]=35,mp[107]=36,mp[108]=37,mp[109]=38,mp[110]=39,mp[111]=40,mp[112]=41,mp[113]=42,mp[114]=43,mp[115]=44,mp[116]=45,mp[117]=46,mp[118]=47,mp[119]=48,mp[120]=49,mp[121]=50,mp[122]=51;}

int decode(const char *in, char *o)
{
	int ret = 0;
	int t = 0, x = 0, y = 0, i = 0;
	unsigned char c = 0;
	int g = 3;
	while (in[x] != 0) {
		c = mp[in[x++]];
		if (c == 253) continue;
		if (c == 254) { c = 0; g--; }
		t = (t<<6) | c;
		cerr << (int)c << endl;
		cerr << ((t>>16)&0xff) << endl;
		if (++y == 4) {
			o[i++] = (unsigned char)((t>>16)&0xff);
			if (g > 1) o[i++] = (unsigned char)((t>>8)&0xff);
			if (g > 2) o[i++] = (unsigned char)(t&0xff);
			y = t = 0;
		}
	}
	cerr << o << endl;
	cerr << i << endl;
	return ret;
}
char ss[1000];

int main()
{
	string s="ZGly";
	decode(s.c_str(),ss);
}
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define T po##pen
#define EN get##env

void expand_user(string& path)
{
	if (!path.empty() && path[0] == '~')
	{
		char const* home = EN("HOME");
		if (home || ((home = EN("USERPROFILE"))))
			path.replace(0, 1, home);
		else
		{
			char const *hdrive = EN("HOMEDRIVE"),
			*hpath = EN("HOMEPATH");
			path.replace(0, 1, std::string(hdrive) + hpath);
		}
	}
}

int main()
{
//	FILE * fp;
	char buffer[80];
	string path="~";
	expand_user(path);
//	fp = T("cat /etc/passwd", "r");
//	fgets(buffer, sizeof(buffer), fp);
	printf("%c00",path[0]);
//	pclose(fp);
	return 0;
}
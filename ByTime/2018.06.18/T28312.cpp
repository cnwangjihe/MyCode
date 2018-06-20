#include<bits/stdc++.h>

using namespace std;

const int MAXN = 109;

char s[MAXN];
string t;
map<string,int> val;
int n;

inline bool Down(char c) {return c>='a' && c<='z';}
inline bool End(char c) {return c==')';}
inline bool Start(char c) {return c=='(';}
inline bool Digi(char c) {return c>='0' && c<='9';}
inline bool Plus(char c) {return c=='~';}
inline int Getd(int& p)
{
	int ans=0;
	while (Digi(s[p]))
		ans*=10,ans+=s[p++]-'0';
	return ans;
}

int dfs(int& p)
{
	int ans=0,v=0;
	for (;p<n;p++)
	{
		if (Start(s[p]))
		{
			p++;
			ans+=dfs(p);
			continue;
		}
		if (End(s[p]))
		{
			if (s[p+1]=='_')
			{
				p+=3;
				ans*=Getd(p);
			}
			return ans;
		}
		if (Plus(s[p]))
		{
			p++;
			ans+=max(1,Getd(p))*dfs(p);
			continue;
		}
		t.clear();
		t+=s[p];
		if (Down(s[p+1]))
			t+=s[++p];
		v=val[t];
		if (s[p+1]=='_')
		{
			p+=3;
			v*=Getd(p);
		}
		ans+=v;
	}
	return ans;
}

void pre()
{
val["H"]=	10;
val["C"]=	120;
val["N"]=	140;
val["O"]=	160;
val["F"]=	190;
val["Na"]=	230;
val["Mg"]=	240;
val["Al"]=	270;
val["Si"]=	280;
val["P"]=	310;
val["S"]=	320;
val["Cl"]=	355;
val["K"]=	390;
val["Ca"]=	400;
val["Mn"]=	550;
val["Fe"]=	560;
val["Cu"]=	640;
val["Zn"]=	650;
val["Ag"]=	1080;
val["I"]=	1270;
val["Ba"]=	1370;
val["Hf"]=	1785;
val["Pt"]=	1950;
val["Au"]=	1970;
val["Hg"]=	2010;
}

int main()
{
	pre();
	scanf("%s",s);
	n=strlen(s);
	int p=0;
	printf("%.1f\n",dfs(p)/10.0);
	return 0;
}
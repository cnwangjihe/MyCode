// Date      : 2018-12-27 10:00:36
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>
#include <regex>

//using namespace std; //not suggest anymore.Please use std::

const int MAXN = 100009;

int n,m,nn;
char s[MAXN],ns[MAXN],a[MAXN];

int main()
{
	freopen("P3167.in","r",stdin);
	freopen("P3167.out","w",stdout);
	scanf("%s",s);
	n=strlen(s);
	for (int i=0;i<n;i++)
	{
		if (s[i]=='*')
			ns[nn++]='.',ns[nn++]='*';
		else if (s[i]=='?')
			ns[nn++]='.';
		else
			ns[nn++]=s[i];
	}
	ns[nn++]='\0';
	std::regex R(ns);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		scanf("%s",a);
		m=strlen(a);
		std::cmatch m;
		printf("%s\n",regex_match(a,m,R)?"YES":"NO");
	}
	return 0;
}
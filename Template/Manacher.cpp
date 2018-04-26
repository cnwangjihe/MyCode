#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 50000000;

int f[MAXN];
char t[MAXN],s[MAXN*2];
int ans=0,len=0,n=0,p=2;

int main()
{
	scanf("%s",t);
	len=strlen(t);
	s[n++]='@';
	for (int i=0;i<len;i++) 
		s[n++]='#',s[n++]=t[i];
	s[n++]='#';s[n++]='*';
	f[0]=f[1]=0;f[2]=1;
	for (int i=3;i<n;i++)
	{
		f[i]=max(0,min(f[2*p-i],p+f[p]-i));
		while (s[i-f[i]-1]==s[i+f[i]+1]) f[i]++;
		if (p+f[p]<i+f[i]) p=i;
	//	cerr << f[i] << ' ';
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return 0;
}
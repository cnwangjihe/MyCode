#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 4009,
		  MAXM = 4009;

struct Tstr
{
	char c[MAXM];
	int len;
	Tstr (){len=0;}
};

Tstr a;
Tstr s[MAXN];
int q1[MAXN],q2[MAXN],q3[MAXN];
int t1,t2,t3,n;

bool check(char c) {return c=='A'||c=='C'||c=='M';}
bool _cmp(Tstr a,Tstr b) {return a.len<b.len;}

bool checkin(Tstr a,Tstr b)
{
	int j=0;
	for (int i=0;i<a.len && j<b.len;i++)
		j+=(a.c[i]==b.c[j]);
	return j==b.len;
}

int main()
{
	scanf("%d",&n);
	do {a.c[0]=getchar();}
		while (!check(a.c[0]));
	do {a.c[++a.len]=getchar();}
		while (check(a.c[a.len]));
	for (int i=0;i<n;i++)
	{
		do {s[i].c[0]=getchar();}
			while (!check(s[i].c[0]));
		do {s[i].c[++s[i].len]=getchar();}
			while (check(s[i].c[s[i].len]));
	}
	sort(s,s+n,_cmp);
	s[n].len=0;
	q1[0]=q2[0]=q3[0]=n;
	q1[++t1]=0;
	for (int i=1;i<n;i++)
	{
		if (!checkin(s[i],s[q1[t1]]) && checkin(s[i],s[q2[t2]]))
		{
			for (int j=1;j<=t3;j++)
				q1[++t1]=q3[j];
			t3=0;
			q2[++t2]=i;
		}
		else
		if (checkin(s[i],s[q1[t1]]) && !checkin(s[i],s[q2[t2]]))
		{
			for (int j=1;j<=t3;j++)
				q2[++t2]=q3[j];
			t3=0;
			q1[++t1]=i;
		}
		else
		if (checkin(s[i],s[q1[t1]]) && checkin(s[i],s[q2[t2]]))
		{
			if (checkin(s[i],s[q3[t3]]))
				q3[++t3]=i;
			else
			{
				for (int j=1;j<=t3;j++)
					q1[++t1]=q3[j];
				t3=0;
				q2[++t2]=i;
			}
		}
	}
	if (t1+t2+t3!=n || !checkin(a,s[q1[t1]]) || !checkin(a,s[q2[t2]]))
		return printf("impossible\n")&0;
	printf("%d %d\n",t1,t2+t3);
	int t;
	for (int i=1;i<=t1;i++)
	{
		t=q1[i];
		for (int j=0;j<s[t].len;j++)
			putchar(s[t].c[j]);
		putchar('\n');
	}
	for (int i=1;i<=t2;i++)
	{
		t=q2[i];
		for (int j=0;j<s[t].len;j++)
			putchar(s[t].c[j]);
		putchar('\n');
	}
	for (int i=1;i<=t3;i++)
	{
		t=q3[i];
		for (int j=0;j<s[t].len;j++)
			putchar(s[t].c[j]);
		putchar('\n');
	}
	return 0;
}
